/*
 * TWIJob.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWIJOB_H_
#define CODE_TWI_TWIJOB_H_

#include <avr/io.h>

// TWI_Job interface class to offer function handling for TWI coms.
class TWI_Job {
private:
	TWI_Job *nextNode;
	static TWI_Job *nodeEnd;

	uint8_t jobStatus = 0;

public:

	TWI_Job();

	// BEGIN and END operations for TWI coms
	virtual void beginOperation();
	virtual void endOperation();

	// END operation.
	virtual void error();

	static TWI_Job * getHeadNode();
	TWI_Job * getNextNode();
};

#endif /* CODE_TWI_TWIJOB_H_ */
