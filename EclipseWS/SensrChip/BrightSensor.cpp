/*
 * BrightSensor.cpp
 *
 *  Created on: 23.04.2016
 *      Author: xasin
 */

#include "BrightSensor.h"


BrightSensor::BrightSensor() {
}

void BrightSensor::adc_update() {
	if(ADC_Lib::measuredPin == B_PIN)
		this->bLevel = ADC_Lib::lastResult >> 2;	// Down-Shift to convert from 10-bit to 8-bit
}

void BrightSensor::update() {
	ADC_Lib::start_measurement(B_PIN);
}

void BrightSensor::endTransmission() {
	if(TWI_Handler::IO.buf.peek() == COMS_BRIGHT)
		this->jobStatus = 1;
}

void BrightSensor::beginTransmission() {
	TWI_Handler::IO.buf.queue(this->bLevel);
	this->jobStatus = 0;
}
