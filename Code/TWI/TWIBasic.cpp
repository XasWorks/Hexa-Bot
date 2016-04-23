/*
 * TWIBasic.cpp
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#include "TWIBasic.h"

TWI_Basic *TWI_Basic::TWISys = 0;

TWI_Basic::TWI_Basic() {
	// Activate TWI and Interrupt
	TWCR = (1<< TWEN | 1<< TWIE | 1<< TWEA);

	// TODO add proper speed system.
	// Fixed speed to ~100kHz
	TWBR = 100;

	sei();
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

bool TWI_Basic::handleIdle() {
	switch(this->readSR()) {
	// Do pretty much nothing while the TWI is idle
	case TWI_IDLE:
		this->onIdle();
	break;

	// Load the address (fist buffer value) into TWDR after having sent the START (or repeated start)
	case TWI_M_REPSTART:
	case TWI_M_START:
		this->load(this->buf.read());
		this->noStart();
	break;

	default:
		return false;
	break;
	}
	return true;
}
bool TWI_Basic::handleMT() {
	switch(this->readSR()) {
	// Load and send further data bytes
	case TWI_MT_SLA_ACK:
	case TWI_MT_DATA_ACK:
		if(this->buf.isAvailable() != 0) {
			this->load(this->buf.read());
		}
		else {
			this->onMTFinish();
		}
	break;

	default:
		return false;
	break;
	}
	return true;
}
bool TWI_Basic::handleMR() {
	switch(this->readSR()) {
	// Wait for the slave to send first byte
		case TWI_MR_SLA_ACK:
			if(--this->readLength == 0)	// Send a NACK if enough data has been received
				this->NACK();

		break;

		// Read in a Byte.
		case TWI_MR_DATA_ACK:
			this->buf.queue(TWDR);

			if(--this->readLength == 0)	// Send a NACK if enough data has been received
				this->NACK();

		break;

		// Read in the final data byte
		case TWI_MR_DATA_NACK:
			this->buf.queue(TWDR);

			this->ACK(); 				// Set ACK again.
			this->onMRFinish();
		break;

		default:
			return false;
		break;
		}
	return true;
}
bool TWI_Basic::handleST() {
	switch(this->readSR()) {
	case TWI_ST_SLA_ACK:
		this->onSTStart();

		this->load(buf.read());
	break;

	case TWI_ST_DATA_ACK:
		this->load(buf.read());
	break;

	case TWI_ST_DATA_LAST:
	case TWI_ST_DATA_NACK:
		buf.clear();
	break;

	default:
		return false;
	break;
	}
	return true;
}
bool TWI_Basic::handleSR() {
	switch(this->readSR()) {
	case TWI_SR_SLA_ACK:
	case TWI_SR_GC_ACK:
	break;

	case TWI_SR_DATA_ACK:
	case TWI_SR_DATA_NACK:
	case TWI_SR_GC_DATA_ACK:
	case TWI_SR_GC_DATA_NACK:
		this->buf.queue(TWDR);
	break;

	case TWI_SR_STOP:
		this->onSRFinish();
	break;

	default:
		return false;
	break;
	}
	return true;
}

void TWI_Basic::update() {
	if(	!this->handleIdle() 	&&
		!this->handleMT() 		&&
		!this->handleMR()		&&
		!this->handleST()		&&
		!this->handleSR() )
		this->onError();

	this->clearTWINT();
}

void TWI_Basic::onIdle() {
	if(this->buf.isAvailable())
		this->start();
}
void TWI_Basic::onError() {
	this->buf.clear();
	TWCR = (1<< TWEN | 1<< TWIE | 1<< TWEA | 1<< TWSTO);
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
