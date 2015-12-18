/*
 * I2CHandler.h
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CHANDLER_H_
#define CODE_I2C_I2CHANDLER_H_

#define I2C_S_START			0x08
#define I2C_S_REPSTART		0x10

#define I2C_S_SLAW_ACK		0x18
#define I2C_S_SLAW_NACK		0x20

#define I2C_S_SLAR_ACK 		0x40
#define I2C_S_SLAR_NACK		0x48

#define I2C_S_DATA_ACK		0x28
#define I2C_S_DATA_NACK		0x30

#define I2C_S_REDA_ACK 		0x50
#define I2C_S_REDA_NACK 	0x58

#define I2C_S_MT_ARB_LOST	0x38

#define I2C_IDLE 0
#define I2C_MASTER_TRANSMIT 1
#define I2C_MASTER_READ 2

#include <avr/io.h>
#include "Buffer.h"

#include "I2CJob.h"

class I2CHandler {
protected:
	Buffer input;
	Buffer output;

	volatile uint8_t mode;

	I2CJob *currentJob = 0;

	void clearTWINT();
	void ACK();
	void NACK();
	void start();
	void stop();
	void load(uint8_t data);
	uint8_t readSR();


public:
	I2CHandler(uint8_t ID, uint8_t mode);

	bool isReady();
	void flush();

	void queueOut(uint8_t *msg, uint8_t length);
	void queueOut(uint8_t msg);
	void beginOperation(uint8_t mode);

	void update();
};

#endif /* CODE_I2C_I2CHANDLER_H_ */
