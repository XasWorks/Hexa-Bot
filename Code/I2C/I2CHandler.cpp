/*
 * I2CHandler.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#include <util/delay.h>

#include "I2CHandler.h"


void I2CHandler::clearTWINT() {
	TWCR |= (1<< TWINT);
}

void I2CHandler::ACK() {
	TWCR |= (1<< TWEA);
}

void I2CHandler::NACK() {
	TWCR &= ~(1<< TWEA);
}

void I2CHandler::start() {
	//Set a start bit condition on the TWI Control
	TWCR |= (1<< TWEN | 1<< TWSTA | 1<< TWINT);
}

void I2CHandler::stop() {
	TWCR |= (1<< TWEN | 1<< TWSTO);
	this->mode = I2C_IDLE;
}

void I2CHandler::load(uint8_t data) {
	TWCR &= ~(1<< TWSTA);
	TWDR = data;
}

uint8_t I2CHandler::readSR() {
	return TWSR & ~(1<< TWPS0 | 1<< TWPS1);
}

I2CHandler::I2CHandler(uint8_t ID, uint8_t mode) {
	//Activate Pull-UPs
	PORTC |= (1<< PC5 | 1<< PC4);

	//Set the speed to 100kHz - TODO add proper speed setting.
	TWBR = 72;

	//Set the TWI Address
	TWAR = (ID << 1);

	//Enable ISR
	TWCR |= (1<< TWIE);
}

bool I2CHandler::isReady() {
	return (this->mode == I2C_IDLE);
}

void I2CHandler::flush() {
	while(this->isReady() == false) {
		_delay_ms(1);
	}
}

void I2CHandler::queueOut(uint8_t *msg, uint8_t length) {
	if(this->mode == I2C_IDLE) {
		for(uint8_t i=0; i< length; i++) {
			this->output.queue(msg[i]);
		}
	}
}

void I2CHandler::queueOut(uint8_t msg) {
	if(this->mode == I2C_IDLE) {
		this->output.queue(msg);
	}
}

void I2CHandler::beginOperation(uint8_t mode) {
	if(this->output.isAvailable() != 0) {
		this->mode = mode;
		this->start();
	}
}

void I2CHandler::update() {
	switch(3) {
	case I2C_MASTER_TRANSMIT:
		if(this->output.isAvailable() != 0)
			this->load(this->output.read());
		else {
			if(this->currentJob != 0)
				this->currentJob->I2CFinish();
			else
				this->stop();
		}
	break;
	}

	this->clearTWINT();
}
