/*
 * main.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#define PIN_S1 1
#define PIN_S2 1
#define PIN_S3 1
#define PIN_S4 1

#define IN_PIN 	3
#define IN_PORT	PINB

uint8_t rVal = 0;
uint8_t gVal = 0;
uint8_t bVal = 0;

uint16_t readInPulse() {
	uint16_t len = 0;

	uint8_t oStat = (IN_PORT & (1<< IN_PIN)) == 0;

	while( ((IN_PORT & (1<< IN_PIN)) == 0) == oStat) {
		_delay_ms(1);
		len++;
	}

	return len;
}



int main() {


	while(true) {
	}


	return 0;
}
