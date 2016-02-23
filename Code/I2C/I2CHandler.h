/*
 * I2CHandler.h
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CHANDLER_H_
#define CODE_I2C_I2CHANDLER_H_

#include "BasicI2C.h"

#define I2C_IDLE 0
#define I2C_MASTER_TRANSMIT 1
#define I2C_MASTER_READ 2

#include <avr/io.h>
#include "Buffer.h"

#include "I2CJob.h"
#include "../Updatable.h"

class I2CHandler : Updatable, BasicI2C {
protected:
	Buffer input;
	Buffer output;

	I2CJob *currentJob = 0;


public:
	I2CHandler(uint8_t ID, uint8_t mode);

	void flush();

	void queueOut(uint8_t *msg, uint8_t length);
	void queueOut(uint8_t msg);
	void beginOperation(I2CJob *job);

	void update();
};

#endif /* CODE_I2C_I2CHANDLER_H_ */
