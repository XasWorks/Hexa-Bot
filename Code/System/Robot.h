/*
 * Robot.h
 *
 *  Created on: 11.01.2016
 *      Author: xasin
 */

#ifndef CODE_SYSTEM_ROBOT_H_
#define CODE_SYSTEM_ROBOT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../Movement/Locomotor.h"

#define F_ISR1 1000
#define F_CAL  100

#define STEPPING 16

class Robot {
public:

	Robot(void);

	void init(void);
	void update(void);

};

#endif /* CODE_SYSTEM_ROBOT_H_ */
