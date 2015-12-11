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
#define F_CAL  50

#define F_REACT 30

#define STEPPING 16

TranslativeStepper stepA = TranslativeStepper(&PORTD, 0, F_ISR1/F_CAL, STEPPING, 35, -30, 75);
TranslativeStepper stepB = TranslativeStepper(&PORTD, 2, F_ISR1/F_CAL, STEPPING, 35, 30, 75);
TranslativeStepper stepC = TranslativeStepper(&PORTD, 4, F_ISR1/F_CAL, STEPPING, 35, 180, 75);

Locomotor test = Locomotor(&stepA, &stepB, &stepC, F_CAL);

uint16_t prescaler = 0;

volatile uint16_t react_prescaler=0;

ISR(TIMER1_COMPA_vect) {
	//Update the stepper motor controllers
	stepA.update();
	stepB.update();
	stepC.update();

	//Software prescaler for slower ISR for calculation updating
	prescaler++;
	if(prescaler == F_ISR1/F_CAL) {
		test.update();
		prescaler = 0;
	}

	if(react_prescaler != F_ISR1/F_REACT)
		react_prescaler++;
}

int main() {

	DDRC |= (0b100);
	PORTC |= (1<<2);

	//CTC Register 1A set up for F_ISR Speed
	OCR1A = F_CPU/64/F_ISR1 -1;
	//Clock select to 64-prescaler, CTC mode
	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	//Timer output/compare match 1 A bit set
	TIMSK1 |= (1<< OCIE1A);

	//Enable global interrupts
	sei();


	//Sensor input pin configuration
	PORTC |= (0b11);

	_delay_ms(500);

#define ROT_SPEED 50
#define DRIVE_SPEED 200

#define ACCELL 200/3

	test.setSpeed(0);
	test.setRotationSpeed(90);
	test.setAcceleration(ACCELL);

	while(true) {
		if(test.atPosition())
			test.moveTowards(75);

		if(test.atRotation()) {

			if((PINC & 1) == 0) {
				test.rotateBy(1);
				test.setSpeed(ROT_SPEED);
			}
			else if((PINC & 2) == 0) {
				test.rotateBy(-1);
				test.setSpeed(ROT_SPEED);
			}
			else {
				test.accelerateTo(DRIVE_SPEED);
			}
		}
	}
}
