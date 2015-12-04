/*
 * I2CHandler.h
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CHANDLER_H_
#define CODE_I2C_I2CHANDLER_H_

#include "Buffer.h"
#include <avr/io.h>


class I2CHandler {
private:
	Buffer input();
	Buffer output();

	void start();
	void stop();
	uint8_t readSR();
	void load(uint8_t data);

public:
	I2CHandler(uint8_t ID, uint8_t SPEED, uint8_t mode);

	void update();
};

#endif /* CODE_I2C_I2CHANDLER_H_ */
