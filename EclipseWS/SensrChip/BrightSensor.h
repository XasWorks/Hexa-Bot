/*
 * BrightSensor.h
 *
 *  Created on: 23.04.2016
 *      Author: xasin
 */

#ifndef BRIGHTSENSOR_H_
#define BRIGHTSENSOR_H_

#include "Code/TWI/TWIHandler.h"
#include "Code/ADC/ADC_Lib.h"
#include "Code/ComsCodes.h"

#define B_PIN 1

class BrightSensor : TWI_S_Job {
private:
	uint16_t bLevel = 0;

public:
	BrightSensor();

	void adc_update();
	void update();

	void endTransmission();
	void beginTransmission();
};

#endif /* BRIGHTSENSOR_H_ */
