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
	TWCR |= (1<< TWSTA | 1<< TWINT);
}
void I2CHandler::stop() {
	TWCR |= (1<< TWSTO);
	this->mode = I2C_IDLE;
}

uint8_t I2CHandler::readSR() {
	return (TWSR & 0xF8);
}

I2CHandler::I2CHandler(uint8_t ID, uint8_t mode) {
	//Activate Pull-UPs
	PORTC |= (1<< PC5 | 1<< PC4);

	//Set the speed to 100kHz - TODO add proper speed setting.
	TWBR = 255;
	TWCR |= 0b11;

	//Set the TWI Address
	TWAR = (ID << 1);

	//Enable ISR
	TWCR |= (1<< TWIE | 1<< TWEN);
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
	if((TWCR & (1<< TWINT)) == 0)
		PORTB |= (1<< PB4);

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
		PORTB |= (1<< PB5);
		this->stop();
	break;
	}

	this->clearTWINT();
}
