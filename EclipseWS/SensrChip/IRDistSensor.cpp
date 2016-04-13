/*
 * IRDistSensor.cpp
 *
 *  Created on: 11.04.2016
 *      Author: xasin
 */

#include "IRDistSensor.h"

IRDistSensor::IRDistSensor() {

}

void IRDistSensor::adc_update() {
	if(ADC_Lib::measuredPin == IR_PIN)
		this->irDistance = (uint8_t) ((IR_MIN_DIST * IR_MAX_VALUE) / ADC_Lib::lastResult);
}

void IRDistSensor::update() {
	ADC_Lib::start_measurement(IR_PIN);
}

void IRDistSensor::endTransmission() {
	if(TWI_Handler::IO.buf.peek() == COMS_IRDIST)
		this->jobStatus = 1;
}
void IRDistSensor::beginTransmission() {
	TWI_Handler::IO.buf.queue(irDistance);
}
