#include <inttypes.h>
#include <compat/twi.h>

#include "twi_master.h"

// inspired by Peter Fleury's code found at /keyboards/ergodone/twimaster.c

#define SCL_CLOCK SCL_CLOCK_400_MHZ

#define S(N, REG) (N<<REG)
#define S1(REG) S(1, REG)

void twi_init(void) {
	STATUS_REG = 0;
	// TODO: does this correspond to clock somehow?
	// TODO: magic number
	BIT_RATE_REG = 10;
}

unsigned char twi_start(unsigned char address) {
	CONTROL_REG = S1(INTERRUPT_CB) | S1(START_CONDITION_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;

	if ((CURRENT_STATUS != TW_START) && (CURRENT_STATUS != TW_REP_START)) return 1;

	DATA_REG = address;
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;

	if ((CURRENT_STATUS != TW_MT_SLA_ACK) && (CURRENT_STATUS != TW_MR_SLA_ACK)) return 1;

	return 0;
}

void twi_start_wait(unsigned char address) {
twi_start_wait:
	CONTROL_REG = S1(INTERRUPT_CB) | S1(START_CONDITION_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;
	if ((CURRENT_STATUS != TW_START) && (CURRENT_STATUS != TW_REP_START)) goto twi_start_wait;
	DATA_REG = address;
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;
	if ((CURRENT_STATUS == TW_MT_SLA_NACK) || (CURRENT_STATUS == TW_MR_DATA_NACK))
	{
		CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB) | S1(STOP_CONDITION_CB);
		WAIT_FOR_STOP;
		goto twi_start_wait;
	}
}

unsigned char twi_rep_start(unsigned char address) {
	return twi_start( address );
}

void twi_stop(void) {
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB) | S1(STOP_CONDITION_CB);
	while(CONTROL_REG & S1(STOP_CONDITION_CB));
}

unsigned char twi_write( unsigned char data ) {
	DATA_REG = data;
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;
	if (CURRENT_STATUS != TW_MT_DATA_ACK) return 1;
	return 0;
}

unsigned char twi_read_ack(void) {
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB) | S1(ENABLE_ACK_CB);
	WAIT_FOR_INTERRUPT;
	return DATA_REG;
}

unsigned char twi_read_nak(void) {
	CONTROL_REG = S1(INTERRUPT_CB) | S1(TWI_ENABLE_CB);
	WAIT_FOR_INTERRUPT;
	return DATA_REG;
}
