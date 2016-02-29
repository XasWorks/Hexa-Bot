/*
 * TWIJob.h
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWIJOB_H_
#define CODE_TWI_TWIJOB_H_

// TWI_Job interface class to offer function handling for TWI coms.

class TWI_Job {
public:

	static TWI_Job *nodeEnd;

	TWI_Job *nextNode;

	TWI_Job();

	virtual void beginOperation();
	virtual void endOperation();

	virtual void error();
};

#endif /* CODE_TWI_TWIJOB_H_ */
