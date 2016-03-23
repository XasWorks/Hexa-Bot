/*
 * ServoController.h
 *
 *  Created on: Mar 18, 2016
 *      Author: xasin
 */

#ifndef SERVOCONTROLLER_H_
#define SERVOCONTROLLER_H_

#include "Code/TWI/TWIJob.h"
#include "Code/TWI/TWIHandler.h"
#include "Code/ComsCodes.h"

class ServoController : public TWI_M_Job {
public:
	uint8_t servo = 0;

	ServoController();

	void setServo(uint8_t level);

	void beginOperation();
};

#endif /* SERVOCONTROLLER_H_ */
