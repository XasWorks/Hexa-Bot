/*
 * I2CHandler.h
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CHANDLER_H_
#define CODE_I2C_I2CHANDLER_H_

#define I2CMODE_IDLE 0
#define I2CMODE_TRANSMIT 1

#include <avr/io.h>
#include "Buffer.h"


class I2CHandler {
private:
	Buffer input;
	Buffer output;

	volatile uint8_t mode;

	void clearTWINT();
	void ACK();
	void NACK();
	void start();
	void stop();
	void load(uint8_t data);
	uint8_t readSR();


public:
	I2CHandler(uint8_t ID, uint8_t mode);

	void transmit(uint8_t *DATA, uint8_t length);
	void update();
};

#endif /* CODE_I2C_I2CHANDLER_H_ */
