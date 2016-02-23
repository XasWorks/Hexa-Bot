
#include "BasicI2C.h"

void BasicI2C::clearTWINT() {
	TWCR |= (1<< TWINT);
}

void BasicI2C::ACK() {
	TWCR |= (1<< TWEA);
}
void BasicI2C::NACK() {
	TWCR &= ~(1<< TWEA);
}
void BasicI2C::start() {
	//Set a start bit condition on the TWI Control
	TWCR |= (1<< TWSTA | 1<< TWINT);
}
void BasicI2C::stop() {
	TWCR |= (1<< TWSTO);
}

uint8_t BasicI2C::readSR() {
	return (TWSR & 0xF8);
}
