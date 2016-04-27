/*
 * ADC.cpp
 *
 *  Created on: 24.03.2016
 *      Author: xasin
 */

#include "ADC_Lib.h"

namespace ADC_Lib {
	volatile uint8_t toMeasurePins = 0;
	volatile uint8_t status = ADC_IDLE;

	volatile uint16_t 	lastResult = 0;
	volatile uint8_t 		measuredPin = 0;

	void init(uint8_t prescaler) {
		ADCSRA = (1<< ADEN | 1<< ADIE | (prescaler << ADPS0));

		ADMUX = (1<< REFS1 | 1<< REFS0);
	}

	uint8_t selectNexPin() {
		for(uint8_t i=7; i >= 0; i--) {
			if((toMeasurePins & (1<<i)) != 0) {
				return i;
			}
		}
	}

	void update() {
		lastResult = ADC;
		measuredPin = ADMUX & 0b11111;

		toMeasurePins &= ~(1<< measuredPin);

		status = ADC_IDLE;
		if(toMeasurePins != 0) {
			start_measurement(selectNexPin());
		}
	}

	void start_measurement(uint8_t pin) {
		if(status == ADC_IDLE) {
			ADMUX &= ~(0b11111);
			ADMUX |= (pin & 0b11111);

			ADCSRA |= (1<< ADSC);

			status = ADC_RUNNING;
		}
		else if(status == ADC_RUNNING) {
			toMeasurePins |= (1<<pin);
		}
	}

	uint16_t measure(uint8_t pin) {
		start_measurement(pin);
		while(measuredPin != pin) {}

		return lastResult;
	}
}
