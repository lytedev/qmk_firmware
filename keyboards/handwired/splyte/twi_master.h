#pragma once

#include <avr/io.h>

// control bits
// source: https://www.exploreembedded.com/wiki/Basics_of_I2C_with_AVR
#define INTERRUPT_CB TWINT
#define ENABLE_ACK_CB TWEA
#define START_CONDITION_CB TWSTA
#define STOP_CONDITION_CB TWSTO
#define WRITE_COLLISION_CB TWWC
#define TWI_ENABLE_CB TWEN
#define INTERRUPT_ENABLE_CB TWIE

#define START_COND_CB START_CONDITION_CB
#define STOP_COND_CB STOP_COND_CB

// status bits
// source: https://www.microchip.com/webdoc/AVRLibcReferenceManual/ch20s33s01.html

// registers
#define BIT_RATE_REG TWBR
#define CONTROL_REG TWCR
#define DATA_REG TWDR
#define STATUS_REG TWSR
#define ENABLE_REG TWEN
#define MASTER_REG TWSTA
#define STOP_COND_REG TWSTO

// misc constants
#define TWI_READ  1
#define TWI_WRITE 0
#define PRESCALAR_MASK 0xF8         // I don't know where this comes from T_T
#define SCL_CLOCK_100_MHZ  100000L  // TODO: which resistor?
#define SCL_CLOCK_400_MHZ  400000L  // TODO: which resistor?
#define SCL_CLOCK_1700_MHZ 1700000L // TODO: which resistor?

// helpers
#define WAIT_FOR_CONTROL_FLAGS(FLAGS) while(!(CONTROL_REG & FLAGS));
#define WAIT_FOR_INTERRUPT WAIT_FOR_CONTROL_FLAGS(S1(INTERRUPT_CB))
#define WAIT_FOR_START WAIT_FOR_CONTROL_FLAGS(S1(START_CONDITION_CB))
#define WAIT_FOR_STOP WAIT_FOR_CONTROL_FLAGS(S1(STOP_CONDITION_CB))
#define CURRENT_STATUS (TW_STATUS & PRESCALAR_MASK)

extern void twi_init(void);
extern void twi_stop(void);
extern unsigned char twi_start(unsigned char addr);
extern unsigned char twi_rep_start(unsigned char addr);
extern void twi_start_wait(unsigned char addr);
extern unsigned char twi_write(unsigned char data);
extern unsigned char twi_read_ack(void);
extern unsigned char twi_read_nak(void);
extern unsigned char twi_read(unsigned char ack);

#define twi_read(ack)  (ack) ? twi_readAck() : twi_readNak();

/*
modified from Peter Fleury's code
found at /keyboards/ergodone/twimaster.h
original header below
*/

/*************************************************************************
* Title:    C include file for the I2C master interface
*           (i2cmaster.S or twimaster.c)
* Author:   Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury
* File:     $Id: i2cmaster.h,v 1.10 2005/03/06 22:39:57 Peter Exp $
* Software: AVR-GCC 3.4.3 / avr-libc 1.2.3
* Target:   any AVR device
* Usage:    see Doxygen manual
**************************************************************************/
