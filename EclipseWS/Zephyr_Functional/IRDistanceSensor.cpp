/*
 * IRDistanceSensor.cpp
 *
 *  Created on: Apr 13, 2016
 *      Author: xasin
 */

#include "IRDistanceSensor.h"

IRDistanceSensor::IRDistanceSensor() {
	// TODO Auto-generated constructor stub

}

void IRDistanceSensor::beginOperation() {
	if(this->jobStatus == 2) {
		TWI_Handler::IO.buf.queue(0b11110);
		TWI_Handler::IO.buf.queue(COMS_IRDIST);
	}
}

void IRDistanceSensor::endOperation() {
		switch(this->jobStatus--) {
			case 2:
				TWI_Handler::IO.buf.queue(0b11111);
			break;

			case 1:
				this->distance_value = TWI_Handler::IO.buf.read();
				this->mesCount++;
			break;
		}
}

void IRDistanceSensor::update() {
	this->jobStatus = 2;
}

uint8_t IRDistanceSensor::get_distance() {
	return this->distance_value;
}
