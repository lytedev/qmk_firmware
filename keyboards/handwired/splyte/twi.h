#pragma once

#include <avr/io.h>

#define I2C_READ    1
#define I2C_WRITE   0

extern void i2c_init(void);
extern void i2c_stop(void);
extern unsigned char i2c_start(unsigned char addr);
extern unsigned char i2c_rep_start(unsigned char addr);
extern void i2c_start_wait(unsigned char addr);
extern unsigned char i2c_write(unsigned char data);
extern unsigned char i2c_readAck(void);
extern unsigned char i2c_readNak(void);
extern unsigned char i2c_read(unsigned char ack);

void wait_for_transmission(void);

#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak();

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
