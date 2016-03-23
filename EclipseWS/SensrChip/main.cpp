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

ServController sController = ServController();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}


int main() {

	TWI_Handler::IO.setAddress(0b1111);

	DDRD |= (1 << 7);

	// Initialisation of PWM
	DDRB |= (1 << PB3);

	TCCR2A = (1 << COM2A1 | 1 << WGM21 | 1 << WGM20);
	TCCR2B = (1 << CS22 | 1 << CS21);

	while(true) {
	}

	return 0;
}
