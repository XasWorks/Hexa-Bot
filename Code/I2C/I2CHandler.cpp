/*
 * I2CHandler.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#include "I2CHandler.h"

void I2CHandler::start() {
	//Set a start bit condition on the TWI Control
	TWCR |= (1<< TWEN | 1<< TWSTA);
}

void I2CHandler::stop() {
	TWCR |= (1<< TWEN | 1<< TWSTO);
}

uint8_t I2CHandler::readSR() {
	return TWSR & ~(1<< TWPS0 | 1<< TWPS1);
}

void I2CHandler::load(uint8_t data) {
	TWDR = data;
	TWCR |= (1<< TWEN);
}

I2CHandler::I2CHandler(uint8_t ID, uint8_t mode) {
	//Set the speed to 100kHz - TODO add proper speed setting.
	TWBR = 72;

	//Set the TWI Address
	TWAR = ID;
}

void I2CHandler::update() {

}
