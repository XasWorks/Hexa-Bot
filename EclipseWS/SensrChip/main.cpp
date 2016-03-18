/*
 * main.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Code/TWI/TWIHandler.h"
#include "ServController.h"

#define SERV_MIN 50
#define SERV_MAX 150

ServController sController = ServController();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}

void setServo(uint8_t p) {
	OCR2A = SERV_MIN + (p * (SERV_MAX - SERV_MIN) / 255);
}

int main() {

	DDRD |= (1 << 7);

	// Initialisation of PWM
	DDRB |= (1 << PB3);

	TCCR2A = (1 << COM2A1 | 1 << WGM21 | 1 << WGM20);
	TCCR2B = (1 << CS22 | 1 << CS21);

	OCR2A = 63;

	TWI_Handler::IO.setAddress(0x0A);

	while(true) {
	}

	return 0;
}
