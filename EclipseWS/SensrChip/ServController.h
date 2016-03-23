/*
 * ServController.h
 *
 *  Created on: Mar 18, 2016
 *      Author: xasin
 */

#ifndef SERVCONTROLLER_H_
#define SERVCONTROLLER_H_

#include <avr/io.h>

#include "Code/ComsCodes.h"
#include "Code/TWI/TWIJob.h"
#include "Code/TWI/TWIHandler.h"

class ServController: public TWI_S_Job {

public:
	ServController();

	void endTransmission();
};

#endif /* SERVCONTROLLER_H_ */
