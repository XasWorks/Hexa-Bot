/*
 * ADC.cpp
 *
 *  Created on: 24.03.2016
 *      Author: xasin
 */

#include "ADC_Lib.h"

namespace ADC_Lib {

	volatile uint16_t 	lastResult = 0;
	volatile uint8_t 	measuredPin = 0;

	void init(uint8_t prescaler) {
		ADCSRA = (1<< ADEN | 1<< ADIE | (prescaler << ADPS0));

		ADMUX = (1<< REFS1 | 1<< REFS0);
	}

	void update() {
		lastResult = ADC;
		measuredPin = ADMUX & 0b11111;
	}

	void start_measurement(uint8_t pin) {
		ADMUX &= ~(0b11111);
		ADMUX |= (pin & 0b11111);

		ADCSRA |= (1<< ADSC);
	}

	uint16_t measure(uint8_t pin) {
		measuredPin = 255;
		start_measurement(pin);
		while(measuredPin == 255) {}

		return lastResult;
	}
}
