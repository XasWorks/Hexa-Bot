/*
 * main.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/LCD.h"
#include "Code/DriveStepper.h"

DriveStepper stepA(&PORTD,0,5000, 200, 12.732394854, 20, 0);

ISR(TIMER1_COMPA_vect) {
	stepA.update();
	stepA.recalculate();
}

int main() {

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/5000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	stepA.setMovementSpeed(100);
	stepA.setRotationSpeed(200);

	_delay_ms(1000);
	stepA.rotate(2000);
	stepA.moveXY(0, 1000);

	while (true) {
		_delay_ms(10);
	}
}
