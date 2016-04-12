/*
 * Timer1.cpp
 *
 *  Created on: 11.04.2016
 *      Author: xasin
 */

#include "Timer1.h"

namespace Timer1 {
	void set_prescaler(uint8_t prescValue) {
		TCCR1B &= ~(0b00000111);
		TCCR1B |= prescValue;
	}

	void set_OCR1A(uint16_t value) {
		OCR1A = value;
	}

	void set_mode(uint8_t mode) {
		switch(mode) {
		case TIMER1_MODE_CTC:
			TCCR1B |= (1 << WGM12);
			TIMSK1 |= (1 << OCIE1A);
		}
	}
}


