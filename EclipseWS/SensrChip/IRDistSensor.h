/*
 * IRDistSensor.h
 *
 *  Created on: 11.04.2016
 *      Author: xasin
 */

#ifndef IRDISTSENSOR_H_
#define IRDISTSENSOR_H_

#include <avr/io.h>

#include "Code/TWI/TWIHandler.h"
#include "Code/ADC/ADC_Lib.h"

#include "Code/ComsCodes.h"

#define IR_MAX_VALUE 600
#define IR_MIN_DIST  4

#define IR_PIN 0

class IRDistSensor : TWI_S_Job {
private:
	uint8_t irDistance = 0;


public:
	IRDistSensor();

	void update();

	void endTransmission();
	void beginTransmission();
};

#endif /* IRDISTSENSOR_H_ */
