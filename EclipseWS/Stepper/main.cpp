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
#include "Code/PrimitiveStepper.h"
#include "Code/RotaryStepper.h"

RotaryStepper stepA(&PORTD,0,10000,200*8);

volatile uint16_t ms=0;
volatile uint8_t sec=0;
volatile uint8_t min=0;

ISR(TIMER1_COMPA_vect) {
	stepA.update();

	if(++ms == 10000) {
		ms = 0;
		if(++sec == 60) {
			sec = 0;
			if(++min == 60)
				min = 0;
		}
	}
}

int main() {

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/10000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();


	stepA.setSpeed(360*2);

	stepA.rotateTo(360*10);
	stepA.flush();
	stepA.rotateTo(0);
	while (true) {
		_delay_ms(10);
	}
}
