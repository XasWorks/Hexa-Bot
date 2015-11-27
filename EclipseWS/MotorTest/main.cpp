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
#define F_CAL  150

#define F_REACT 20

#define STEPPING 8

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

	_delay_ms(1000);

	test.setSpeed(30);
	test.setRotationSpeed(45);

#define ACCELL 300
#define MAX_SPEED 50

	float accell_speed=0;

	while(true) {


		if(react_prescaler == F_ISR1 / F_REACT) {
			react_prescaler = 0;

			test.moveTowards(20 / F_REACT);


			if((PINC & 1) == 0) {
				if(accell_speed <= MAX_SPEED) {
					accell_speed += ACCELL / F_REACT;
					test.setRotationSpeed(accell_speed);
				}
				test.rotateBy(accell_speed / F_REACT);
			}
			else if((PINC & 2) == 0) {
				if(accell_speed <= MAX_SPEED) {
					accell_speed += ACCELL / F_REACT;
					test.setRotationSpeed(accell_speed);
				}
				test.rotateBy(-accell_speed / F_REACT);
			}
			else
				accell_speed = 0;
		}
	}
}
