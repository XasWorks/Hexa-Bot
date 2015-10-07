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

LCD disp(&PORTA);
RotaryStepper stepA(&PORTD,0,7500,200*4);

volatile uint16_t ms=0;
volatile uint8_t sec=0;
volatile uint8_t min=0;

ISR(TIMER1_COMPA_vect) {
	disp.updateDisplay();
	stepA.update();

	if(++ms == 5000) {
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
	OCR1A =	F_CPU/64/7500 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();


	disp.writeString("Hi!",0);
	stepA.setSpeed(360*4);
	stepA.move(-360*4);
	stepA.flush();
	stepA.setSpeed(360);

	while (true) {
		_delay_ms(10);
		stepA.rotateTo( (uint32_t)(sec*1000+ms/5)*6*(1<<3)/1000,3);
	}
}
