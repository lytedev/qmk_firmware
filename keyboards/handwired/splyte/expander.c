#include <stdbool.h>

#include "action.h"
#include "twi_master.h"
#include "expander.h"
#include "debug.h"

static uint8_t expander_status = 0;
static uint8_t expander_input = 0;

// TODO: grok this code
uint8_t expander_write(uint8_t, uint8_t);
void expander_scan(void);

void expander_config(void) {
	expander_write(EXPANDER_REG_IPOLA, 0xFF);
	expander_write(EXPANDER_REG_GPPUA, 0xFF);
	expander_write(EXPANDER_REG_IODIRB, 0xFF);
}

void expander_init(void) {
	twi_init();
	expander_scan();
}

uint8_t expander_write(uint8_t reg, uint8_t data) {
	if (expander_status == 0) return 0;
	uint8_t ret;
	ret = twi_start(EXPANDER_ADDR | TWI_WRITE);
	if (ret) goto stop;
	ret = twi_write(reg);
	if (ret) goto stop;
	ret = twi_write(data);
stop:
	twi_stop();
	return ret;
}

uint8_t expander_read(uint8_t reg, uint8_t *data) {
	if (expander_status == 0) return 0;
	uint8_t ret;
	ret = twi_start(EXPANDER_ADDR | TWI_WRITE);
	if (ret) goto stop;
	ret = twi_write(reg);
	if (ret) goto stop;
	ret = twi_rep_start(EXPANDER_ADDR | TWI_READ);
	if (ret) goto stop;
	*data = twi_read_nak();
stop:
	twi_stop();
	return ret;
}

void expander_scan(void) {
	uint8_t ret = twi_start(EXPANDER_ADDR | TWI_WRITE);
	if (ret == 0) {
		twi_stop();
		if (expander_status == 0) {
			expander_status = 1;
			expander_config();
			clear_keyboard();
		}
	}
	else {
		if (expander_status == 1) {
			expander_status = 0;
			clear_keyboard();
		}
	}
}

void expander_read_cols(void) {
	expander_read(EXPANDER_REG_GPIOA, &expander_input);
}

uint8_t expander_get_col(uint8_t col) {
	if (col > 4) {
		col++;
	}
	return expander_input & (1<<col) ? 1 : 0;
}

matrix_row_t expander_read_row(void) {
	expander_read_cols();

	/* make cols */
	matrix_row_t cols = 0;
	for (uint8_t col = 0; col < MATRIX_COLS; col++) {
		if (expander_get_col(col)) {
			cols |= (1UL << (MATRIX_COLS - 1 - col));
		}
	}

	return cols;
}

void expander_unselect_rows(void) {
	expander_write(EXPANDER_REG_IODIRB, 0xFF);
}

void expander_select_row(uint8_t row) {
	expander_write(EXPANDER_REG_IODIRB, ~(1<<(row+1)));
}

