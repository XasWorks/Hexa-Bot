/*
 * ADC.h
 *
 *  Created on: 24.03.2016
 *      Author: xasin
 */

#ifndef CODE_ADC_ADC_LIB_H_
#define CODE_ADC_ADC_LIB_H_

#include <avr/io.h>

#define ADC_MAX 1023

#define ADC_PRSC_2 	 	0b001
#define ADC_PRSC_4 	 	0b010
#define ADC_PRSC_8 	 	0b011
#define ADC_PRSC_16  	0b100
#define ADC_PRSC_32  	0b101
#define ADC_PRSC_64  	0b110
#define ADC_PRSC_128 	0b111

#define ADC_IDLE			1
#define ADC_RUNNING		2

namespace ADC_Lib {
	volatile extern uint16_t 	lastResult;
	volatile extern uint8_t 	measuredPin;

	void init(uint8_t prescaler);

	void update();

	void start_measurement(uint8_t pin);

	uint16_t measure(uint8_t pin);
}



#endif /* CODE_ADC_ADC_LIB_H_ */
