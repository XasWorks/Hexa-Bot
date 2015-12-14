/*
 * I2CHandler.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

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

void I2CHandler::startJob(I2CJob *job) {
	this->currentJob = job;
	this->currentJob->I2CInit(&output);
	this->mode = I2C_MASTER_TRANSMIT;
	this->start();
}

void I2CHandler::update() {
	switch(3) {
	case I2C_MASTER_TRANSMIT:
		if(this->output.isAvailable() != 0)
			this->load(this->output.read());
		else {
			this->stop();
			this->currentJob->I2CFinish(&input);
			this->mode = I2C_IDLE;
		}
	break;
	}

	this->clearTWINT();
}
