/*
 * main.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Code/I2C/Buffer.h"

#include "Code/I2C/I2CHandler.h"

I2CHandler test(1, 0);

#define PORTEXP_GPIO 0x12
#define PORTEXP_IODIR 0x00

class PortExp : I2CJob {
private:
	uint8_t address;
	uint16_t outputBuffer = 0;
	I2CHandler *handler;
public:
	PortExp(uint8_t addr, I2CHandler *handler) {
		this->address = addr;
		this->handler = handler;
	}

	void setRegisters(uint16_t outputs, uint8_t reg) {
		handler->flush();
		handler->queueOut(address);
		handler->queueOut(reg);
		handler->queueOut(outputs & (0x00ff));
		handler->queueOut((outputs & (0xff00)) >> 8);

		handler->beginOperation(I2C_MASTER_TRANSMIT);
	}
};

PortExp SensrJob(0b01001110, &test);

ISR(TWI_vect) {
	test.update();
}

int main() {
	DDRB |= (1<< PB5 | 1<< PB4);

	sei();

	SensrJob.setRegisters(0x0000, PORTEXP_IODIR);

	while(1) {
		SensrJob.setRegisters(0xffff, PORTEXP_GPIO);
		_delay_ms(500);
		SensrJob.setRegisters(0x0000, PORTEXP_GPIO);
		_delay_ms(500);
	}

}
