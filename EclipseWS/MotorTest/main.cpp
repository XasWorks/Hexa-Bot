/*
 * main.cpp
 *
 *  Created on: 22.11.2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/Movement/Locomotor.h"

#define F_ISR1 5000
#define F_CAL  400

TranslativeStepper stepA = TranslativeStepper(&PORTD, 0, F_ISR1/F_CAL, 8, 30, 0, 75);
TranslativeStepper stepB = TranslativeStepper(&PORTD, 2, F_ISR1/F_CAL, 8, 30, 120, 75);
TranslativeStepper stepC = TranslativeStepper(&PORTD, 4, F_ISR1/F_CAL, 8, 30, 240, 75);

Locomotor test = Locomotor(&stepA, &stepB, &stepC, F_CAL);

uint16_t prescaler = 0;
ISR(TIMER1_COMPA_vect) {
	//Update the stepper motor controllers
	stepA.update();
	stepB.update();

	//Software prescaler for slower ISR for calculation updating
	prescaler++;
	if(prescaler == F_ISR1/F_CAL) {
		test.update();
		prescaler = 0;
	}
}

int main() {

	//CTC Register 1A set up for F_ISR Speed
	OCR1A = F_CPU/64/F_ISR1 -1;

	//Clock select to 64-prescaler, CTC mode
	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));

	//Timer output/compare match 1 A bit set
	TIMSK1 |= (1<< OCIE1A);

	//Enable global interrupts
	sei();

	_delay_ms(1000);

	test.setSpeed(100);
	test.setRotationSpeed(100);
	test.rotateBy(1000);
	test.moveBy(1000,0);

	while(true) {}
}
