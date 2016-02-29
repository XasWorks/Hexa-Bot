/*
 * TWIBasic.cpp
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#include "TWIBasic.h"

TWI_Basic::TWI_Basic() {
	// TODO Auto-generated constructor stub

}

void TWI_Basic::clearTWINT() {
	// Clear TWINT Flag. (Write logical 1)
	TWCR |= (1<< TWINT);
}

void TWI_Basic::ACK() {
	//Set ACK flag
	TWCR |= (1<< TWEA);
}
void TWI_Basic::NACK() {
	// Clear ACK flag. NOT TWINT!
	TWCR &= ~(1<< TWEA | 1<< TWINT);
}

uint8_t TWI_Basic::readSR() {
	// Read out the status-register, without prescaler bits
	return (TWSR & 0b11111000);
}

void TWI_Basic::start() {
	TWCR |= (1<< TWSTA);
}
void TWI_Basic::noStart() {
	// Clear out TWSTA flag. NOT TWINT!
	TWCR &= ~(1<< TWSTA | 1<< TWINT);
}
void TWI_Basic::stop() {
	TWCR |= (1<< TWSTO);
}

void TWI_Basic::load(uint8_t data) {
	TWDR = data;
}

void TWI_Basic::update() {
	switch (this->readSR()) {
	// Do pretty much nothing while the TWI is idle
	case TWI_IDLE:
		this->onIdle();
	break;

	// Load the address (fist buffer value) into TWDR after having sent the START (or repeated start)
	case TWI_M_REPSTART:
	case TWI_M_START:
		this->load(this->buf.read());
		this->noStart();

		this->clearTWINT();
	break;

	// Load and send further data bytes
	case TWI_MT_SLA_ACK:
	case TWI_MT_DATA_ACK:
		if(this->buf.isAvailable() != 0) {
			this->load(this->buf.read());
		}
		else {
			this->onMTFinish();
		}

		this->clearTWINT();
	break;

	// Wait for the slave to send first byte
	case TWI_MR_SLA_ACK:
		if(--this->readLength == 0)	// Send a NACK if enough data has been received
			this->NACK();

		this->clearTWINT();
	break;

	// Read in a Byte.
	case TWI_MR_DATA_ACK:
		this->buf.queue(TWDR);
		if(--this->readLength == 0)	// Send a NACK if enough data has been received
			this->NACK();

		this->clearTWINT();
	break;

	case TWI_MR_DATA_NACK:
		this->buf.queue(TWDR);

		this->ACK(); 				// Set ACK again.

		this->onMRFinish();

		this->clearTWINT();
	break;


	}
}


void TWI_Basic::onIdle() {
	if(this->buf.isAvailable())
		this->start();
}
void TWI_Basic::onError() {
	this->buf.clear();
	this->stop();
}

void TWI_Basic::onMTFinish() {
	this->stop();
}
void TWI_Basic::onMRFinish() {
	this->buf.clear();
	this->stop();
}
void TWI_Basic::onSRFinish() {}
void TWI_Basic::onSTStart() {}
