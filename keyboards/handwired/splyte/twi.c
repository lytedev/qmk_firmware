#include <inttypes.h>
#include <compat/twi.h>

#include "twi.h"

#define SCL_CLOCK  400000L

void i2c_init(void) {
	TWSR = 0;
	TWBR = 10;
}

void wait_for_transmission() {
	while(!(TWCR & (1<<TWINT)));
}

unsigned char i2c_start(unsigned char address) {
	uint8_t twst;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	wait_for_transmission();
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	wait_for_transmission();
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	return 0;
}

void i2c_start_wait(unsigned char address) {
	uint8_t twst;

	while (1)
	{
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		wait_for_transmission();
		twst = TW_STATUS & 0xF8;
		if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
		TWDR = address;
		TWCR = (1<<TWINT) | (1<<TWEN);
		wait_for_transmission();
		twst = TW_STATUS & 0xF8;
		if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
		{
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
			while(TWCR & (1<<TWSTO));
			continue;
		}
		break;
	}
}

unsigned char i2c_rep_start(unsigned char address) {
	return i2c_start( address );
}

void i2c_stop(void) {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}

unsigned char i2c_write( unsigned char data ) {
	uint8_t twst;
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	wait_for_transmission();
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}

unsigned char i2c_readAck(void) {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	wait_for_transmission();
	return TWDR;
}

unsigned char i2c_readNak(void) {
	TWCR = (1<<TWINT) | (1<<TWEN);
	wait_for_transmission();
	return TWDR;
}

/*
modified from Peter Fleury's code
found at /keyboards/ergodone/twimaster.c
original header below
*/

/*************************************************************************
 * Title:  I2C master library using hardware TWI interface
 * Author:   Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury
 * File:   $Id: twimaster.c,v 1.3 2005/07/02 11:14:21 Peter Exp $
 * Software: AVR-GCC 3.4.3 / avr-libc 1.2.3
 * Target:   any AVR device with hardware TWI
 * Usage:  API compatible with I2C Software Library i2cmaster.h
 **************************************************************************/
