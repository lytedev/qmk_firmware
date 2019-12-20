#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "expander.h"

#ifdef DEBUG_MATRIX_SCAN_RATE
#include  "timer.h"
#endif

#ifdef DEBUG_MATRIX_SCAN_RATE
uint32_t matrix_timer;
uint32_t matrix_scan_count;
#endif

static matrix_row_t matrix[MATRIX_ROWS];
static uint8_t debounce_matrix[MATRIX_ROWS * MATRIX_COLS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

__attribute__ ((weak))
	void matrix_init_user(void) {}

__attribute__ ((weak))
	void matrix_scan_user(void) {}

__attribute__ ((weak))
	void matrix_init_kb(void) {
		matrix_init_user();
	}

__attribute__ ((weak))
	void matrix_scan_kb(void) {
		matrix_scan_user();
	}

inline uint8_t matrix_rows(void) {
	return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
	return MATRIX_COLS;
}

void matrix_init(void) {
	unselect_rows();
	init_cols();

	for (uint8_t i=0; i < MATRIX_ROWS; i++) {
		matrix[i] = 0;
		for (uint8_t j=0; j < MATRIX_COLS; ++j) {
			debounce_matrix[i * MATRIX_COLS + j] = 0;
		}
	}

#ifdef DEBUG_MATRIX_SCAN_RATE
	matrix_timer = timer_read32();
	matrix_scan_count = 0;
#endif

	matrix_init_quantum();
}

void matrix_power_up(void) {

	unselect_rows();
	init_cols();

	for (uint8_t i=0; i < MATRIX_ROWS; i++) {
		matrix[i] = 0;
	}

#ifdef DEBUG_MATRIX_SCAN_RATE
	matrix_timer = timer_read32();
	matrix_scan_count = 0;
#endif
}

matrix_row_t debounce_mask(uint8_t row) {
	matrix_row_t result = 0;
	for (uint8_t j=0; j < MATRIX_COLS; ++j) {
		if (debounce_matrix[row * MATRIX_COLS + j]) {
			--debounce_matrix[row * MATRIX_COLS + j];
		} else {
			result |= (1 << j);
		}
	}
	return result;
}


void debounce_report(matrix_row_t change, uint8_t row) {
	for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
		if (change & (1 << i)) {
			debounce_matrix[row * MATRIX_COLS + i] = DEBOUNCE;
		}
	}
}

uint8_t matrix_scan(void) {
	expander_scan();

#ifdef DEBUG_MATRIX_SCAN_RATE
	matrix_scan_count++;

	uint32_t timer_now = timer_read32();
	if (TIMER_DIFF_32(timer_now, matrix_timer)>1000) {
		print("matrix scan frequency: ");
		pdec(matrix_scan_count);
		print("\n");
		matrix_print();

		matrix_timer = timer_now;
		matrix_scan_count = 0;
	}
#endif

	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		select_row(i);
		wait_us(30); // necessary for stable read values
		matrix_row_t mask = debounce_mask(i);
		matrix_row_t cols = (read_cols(i) & mask) | (matrix[i] & ~mask);
		debounce_report(cols ^ matrix[i], i);
		matrix[i] = cols;

		unselect_rows();
	}

	matrix_scan_quantum();

	return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
	return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
	return matrix[row];
}

void matrix_print(void) {
	print("\nr/c 0123456789ABCDEF\n");
	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		phex(row); print(": ");
		pbin_reverse16(matrix_get_row(row));
		print("\n");
	}
}

uint8_t matrix_key_count(void) {
	uint8_t count = 0;
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		count += bitpop16(matrix[i]);
	}
	return count;
}

/* Column pin configuration
 *
 * Feather 32u4 Bluefruit LE:
 *           5  4  3  2  1  0
 *           F0 F1 F4 F5 F6 F7
 * Expander:
 *           13 12 11 10 9  8
 */
static void init_cols(void) {
	DDRF  &= ~(1<<PF0 | 1<<PF1 | 1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
	PORTF |=  (1<<PF0 | 1<<PF1 | 1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);

	expander_init();
}

static matrix_row_t read_cols(uint8_t row) {
	return expander_read_row() |
		(PINF&(1<<PF0) ? 0 : (1<<0)) |
		(PINF&(1<<PF1) ? 0 : (1<<1)) |
		(PINF&(1<<PF4) ? 0 : (1<<2)) |
		(PINF&(1<<PF5) ? 0 : (1<<3)) |
		(PINF&(1<<PF6) ? 0 : (1<<4)) |
		(PINF&(1<<PF7) ? 0 : (1<<5)) ;
}

/* Row pin configuration
 *
 * Feather 32u4 Bluefruit LE:
 *           0  1  2  3  4
 *           D6 B7 B6 B5 C6
 * Expander:
 *           0  1  2  3  4
 */
static void unselect_rows(void) {
	DDRB  &= ~(1<<PB7 | 1<<PB6 | 1<<PB5);
	PORTB &= ~(1<<PB7 | 1<<PB6 | 1<<PB5);
	DDRD  &= ~(1<<PD6);
	PORTD &= ~(1<<PD6);
	DDRC  &= ~(1<<PC6);
	PORTC &= ~(1<<PC6);

	expander_unselect_rows();
}

static void select_row(uint8_t row) {
	switch (row) {
		case 0:
			DDRD  |=  (1<<PD6);
			PORTD &= ~(1<<PD6);
			break;
		case 1:
			DDRB  |=  (1<<PB7);
			PORTB &= ~(1<<PB7);
			break;
		case 2:
			DDRB  |=  (1<<PB6);
			PORTB &= ~(1<<PB6);
			break;
		case 3:
			DDRB  |=  (1<<PB5);
			PORTB &= ~(1<<PB5);
			break;
		case 4:
			DDRC  |=  (1<<PC6);
			PORTC &= ~(1<<PC6);
			break;
	}

	expander_select_row(row);
}
