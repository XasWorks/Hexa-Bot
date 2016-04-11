/*
 * TWIJob.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWIJOB_H_
#define CODE_TWI_TWIJOB_H_

#include <avr/io.h>

// TWI_M_Job interface class to offer function handling for TWI coms.
class TWI_M_Job {
private:
	TWI_M_Job *nextNode = 0;
	static TWI_M_Job *nodeEnd;

protected:
	uint8_t jobStatus = 0;

public:

	TWI_M_Job();

	// BEGIN and END operations for TWI coms
	virtual void beginOperation();
	virtual void endOperation();

	// ERROR operation, executed if something goes wrong during transmission.
	virtual void error();

	// Return important nodes for the TWI Job search
	static TWI_M_Job * getHeadNode();
	TWI_M_Job * getNextNode();

	// Return the current Job's status
	uint8_t getStatus();
};


class TWI_S_Job {
private:
	TWI_S_Job *nextNode = 0;
	static TWI_S_Job *nodeEnd;

protected:
	uint8_t jobStatus = 0;

public:
	TWI_S_Job();

	// Functions to begin and end transmissions. They are called before (if job status != 0) and after receiving a message (always).
	virtual void beginTransmission();
	virtual void endTransmission();

	static TWI_S_Job * getHeadNode();
	TWI_S_Job * getNextNode();

	uint8_t getStatus();
};
#endif /* CODE_TWI_TWIJOB_H_ */
