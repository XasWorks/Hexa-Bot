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

#define IN_PIN 	0
#define IN_PORT	PINB

uint8_t rVal = 0;
uint8_t gVal = 0;
uint8_t bVal = 0;

uint16_t readInPulse() {
	uint16_t len = 0;

	while( (IN_PORT & (1<< IN_PIN)) != 0) {
	}

	while( (IN_PORT & (1<< IN_PIN)) == 0) {
		_delay_us(1);
		len++;
	}

	return len;
}

void updateColors() {

}

int main() {

	DDRA |= (0b1111);
	PORTB |= (0b1);

	while(true) {
	}


	return 0;
}
