/*
 * main.cpp
 *
 *  Created on: 05.01.2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/LineFollow/LF3Sens.h"

#define F_ISR1 1000

LF3Sens LFSensr = LF3Sens();

ISR(TIMER1_COMPA_vect) {
	LFSensr.update();
}

int main() {

	//CTC Register 1A set up for F_ISR Speed
	OCR1A = F_CPU/64/F_ISR1 -1;
	//Clock select to 64-prescaler, CTC mode
	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	//Timer output/compare match 1A bit set
	TIMSK1 |= (1<< OCIE1A);

	//Enable global interrupts
	sei();


}
