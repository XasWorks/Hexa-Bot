/*
 * LF3Sens.h
 *
 *  Created on: Jan 3, 2016
 *      Author: xasin
 */

#ifndef F_ISR1
#define F_ISR1 1000
#endif

#ifndef CODE_LINEFOLLOW_LF3SENS_H_
#define CODE_LINEFOLLOW_LF3SENS_H_

#define INTSEC_DEFAULT_DIR LF_RIGHT
#define DELAY_VAL F_ISR1 / 10

#include <avr/io.h>
#include "LFBasic.h"

class LF3Sens : public LFBasic {
private:
	//Update delay value, to make sure the sensors can change properly
	uint8_t uDelay = 0;
	//Value of the old sensors, to detect changes
	uint8_t oSens = 0;

	//Update the sensors.
	void setStatus(uint8_t sensors);
public:
	LF3Sens();

	void update();
};

#endif /* CODE_LINEFOLLOW_LF3SENS_H_ */
