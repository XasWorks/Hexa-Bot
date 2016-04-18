/*
 * ServoController.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: xasin
 */

#include "ServoController.h"

ServoController::ServoController() {
	// TODO Auto-generated constructor stub

}

void ServoController::setServo(uint8_t level) {
	this->servo = level;
	this->jobStatus = 1;
}

void ServoController::beginOperation() {
	TWI_Handler::IO.buf.queue(0b11110);
	TWI_Handler::IO.buf.queue(COMS_SERVO);
	TWI_Handler::IO.buf.queue(this->servo);
}
