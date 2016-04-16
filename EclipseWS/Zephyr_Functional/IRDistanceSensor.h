/*
 * IRDistanceSensor.h
 *
 *  Created on: Apr 13, 2016
 *      Author: xasin
 */

#ifndef IRDISTANCESENSOR_H_
#define IRDISTANCESENSOR_H_

#include <avr/io.h>
#include "Code/TWI/TWIHandler.h"

#include "Code/ComsCodes.h"

class IRDistanceSensor : TWI_M_Job {
private:
	uint8_t mesCount = 0;
	uint8_t distance_value = 0;

public:

	void beginOperation();
	void endOperation();

	IRDistanceSensor();

	void update();

	uint8_t get_distance();

};

#endif /* IRDISTANCESENSOR_H_ */
