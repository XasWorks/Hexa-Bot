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

	this->input = new Buffer();
	this->output = new Buffer();

	//Set the speed to 100kHz - TODO add proper speed setting.
	TWBR = 72;

	//Set the TWI Address
	TWAR = (ID << 1);

	//Enable ISR
	TWCR |= (1<< TWIE);
}

//void I2CHandler::transmit(uint8_t *DATA, uint8_t length) {
//	for(uint8_t i=0; i < length; i++) {
//		this->input->queue(DATA[i]);
//	}
//
//	this->mode = I2CMODE_TRANSMIT;
//
//	this->start();
//}

//void I2CHandler::update() {
//	switch(3) {
//	case I2CMODE_TRANSMIT:
//		if(this->input->isAvailable() != 0)
//			this->load(this->input->read());
//		else {
//			this->stop();
//			//this->mode = I2CMODE_IDLE;
//		}
//	break;
//	}
//
//	this->clearTWINT();
//}

