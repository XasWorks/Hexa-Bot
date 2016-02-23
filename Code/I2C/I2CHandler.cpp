/*
 * I2CHandler.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#include <util/delay.h>

#include "I2CHandler.h"


I2CHandler::I2CHandler(uint8_t ID, uint8_t mode) {
	//Activate Pull-UPs
	PORTC |= (1<< PC5 | 1<< PC4);

	//Set the speed to 100kHz - TODO add proper speed setting.
	TWBR = 10;

	//Set the TWI Address
	TWAR = (ID << 1);

	//Enable ISR
	TWCR |= (1<< TWIE | 1<< TWEN);
}

void I2CHandler::flush() {
	while(this->isReady() == false) {
	}
}

void I2CHandler::queueOut(uint8_t *msg, uint8_t length) {
	if(this->readSR() == I2C_S_IDLE) {
		for(uint8_t i=0; i< length; i++) {
			this->output.queue(msg[i]);
		}
	}
}
void I2CHandler::queueOut(uint8_t msg) {
	if(this->readSR() == I2C_S_IDLE) {
		this->output.queue(msg);
	}
}

void I2CHandler::beginOperation(I2CJob *job) {
	if(this->currentJob == NULL) {
		this->currentJob->I2CLoad();

		this->start();
	}
}

void I2CHandler::update() {
	switch(this->readSR()) {
	case I2C_S_START:
		TWDR = this->output.read();
		TWCR &= ~(1<< TWSTA);
	break;

	case I2C_S_SLAW_ACK:
	case I2C_S_DATA_ACK:
		if(this->output.isAvailable() > 0)
			TWDR = this->output.read();
		else
			this->stop();
	break;

	case I2C_S_SLAW_NACK:
	case I2C_S_SLAR_NACK:
	case I2C_S_DATA_NACK:
		this->stop();
	break;
	}

	this->clearTWINT();
}
