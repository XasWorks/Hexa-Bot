/*
 * IRDistSensor.cpp
 *
 *  Created on: 11.04.2016
 *      Author: xasin
 */

#include "IRDistSensor.h"

IRDistSensor::IRDistSensor() {

}

void IRDistSensor::update() {
	this->irDistance = ADC_Lib::measure(IR_PIN);
}

void IRDistSensor::endTransmission() {
	if(TWI_Handler::IO.buf.peek() == COMS_IRDIST)
		this->jobStatus = 1;
}
void IRDistSensor::beginTransmission() {
	TWI_Handler::IO.buf.queue(irDistance);
}
