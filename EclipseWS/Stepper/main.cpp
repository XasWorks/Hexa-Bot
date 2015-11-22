/*
 * main.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/LCD/LCD.h"

#include "Code/Movement/Locomotor.h"

TranslativeStepper stepA(&PORTD,0,10000/400, 1, 20, 0, 10);
Locomotor test(&stepA, 0, 0, 400);

uint16_t prescaler = 0;
ISR(TIMER1_COMPA_vect) {
	stepA.update();

	prescaler++;
	if(prescaler == 10000/400) {
		test.update();
		prescaler = 0;
	}
}

int main() {

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/10000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	_delay_ms(1000);

	test.setSpeed(100);
	test.moveBy(100,100);
	_delay_ms(2000);
	test.moveBy(200,0);

	while (true) {
		_delay_ms(10);
	}
}
