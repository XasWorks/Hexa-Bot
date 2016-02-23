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

#define PORT_S PORTA
#define S1 0
#define S2 1
#define S3 2
#define S4 3

#define IN_PIN 	2
#define IN_PORT	PINB

uint8_t rVal = 0;
uint8_t gVal = 0;
uint8_t bVal = 0;

uint16_t readInPulse() {
	uint8_t len = 0;

	while( (IN_PORT & (1<< IN_PIN)) == 0) {
	}
	while( (IN_PORT & (1<< IN_PIN)) != 0) {
		len++;
	}
	while( (IN_PORT & (1<< IN_PIN)) == 0) {
		len++;
	}
	return len;
}

void sOut(uint8_t bit) {
	_delay_ms(2000);

	PORTA |= 1;
	_delay_ms(500);
	PORTA &= ~1;
	_delay_ms(500);

	if(bit) {
		PORTA |= 1;
		_delay_ms(500);
		PORTA &= ~1;
		_delay_ms(500);
	}
}


void oPut(uint8_t input) {
	for(uint8_t i=0; i<3; i++) {
		sOut((input & (1<< i)) != 0);
	}
	PORTA &= ~(1);
	_delay_ms(8000);
}

void setSPins(uint8_t in) {
	PORTA &= ~(0b110);
	PORTA |= (in << 1);
}

void updateColors() {
	setSPins(0b00);
	rVal = readInPulse();
	setSPins(0b10);
	bVal = readInPulse();
	setSPins(0b11);
	gVal = readInPulse();
}

int main() {

	DDRA 	|= (0b1111111);
	PORTB 	|= (0b100);

	while(true) {

		updateColors();

		uint8_t sColor = 0;
		if(gVal < 50)
			sColor |= (1<< 1);
		if(bVal < 40)
			sColor |= 1;
		if(rVal < 42)
			sColor |= (1<< 2);

		if(sColor == 0b010) {
			PORTA |= 1 << 6;
			_delay_ms(600);
		}
		else
			PORTA &= ~(1<< 6);
	}


	return 0;
}
