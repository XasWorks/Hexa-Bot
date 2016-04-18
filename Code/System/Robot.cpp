/*
 * Robot.cpp
 *
 *  Created on: 11.01.2016
 *      Author: xasin
 */

#ifndef TIMSK1
#define TIMSK1 TIMSK
#endif

#include "Robot.h"

Robot::Robot() {
	_delay_ms(1000);

	//CTC Register 1A set up for F_ISR Speed
	OCR1A = F_CPU/64/F_ISR1 -1;
	//Clock select to 64-prescaler, CTC mode
	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	//Timer output/compare match 1A bit set
	TIMSK1 |= (1<< OCIE1A);

	//Enable global interrupts
	sei();
}

void Robot::update() {
	//Update the stepper motor controllers
	stepA.update();
	stepB.update();
	stepC.update();

	//Software prescaler for slower ISR for calculation updating
	ISR1presc++;
	if(ISR1presc == F_ISR1 / F_CAL) {
		//Re-Enable interrupts
		sei();

		ISR1presc = 0;
		Motor.update();

		TWI_Handler::IO.updateJobs();
	}
}
