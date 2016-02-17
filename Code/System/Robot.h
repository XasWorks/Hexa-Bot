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

#define F_ISR1 5000
#define F_CAL  150

#define STEPPING 16
#define YROT_COMP -0.2

class Robot {
private:
	TranslativeStepper stepA = TranslativeStepper(&PORTD, 0, F_ISR1/F_CAL, STEPPING, 35, -30, 75, YROT_COMP);
	TranslativeStepper stepB = TranslativeStepper(&PORTD, 2, F_ISR1/F_CAL, STEPPING, 35, 30, 75, YROT_COMP);
	TranslativeStepper stepC = TranslativeStepper(&PORTD, 4, F_ISR1/F_CAL, STEPPING, 35, 180, 75, YROT_COMP);

	//ISR Prescaler value
	uint16_t ISR1presc = 0;

public:

	Locomotor Motor = Locomotor(&stepA, &stepB, &stepC, F_CAL);

	Robot(void);

	void init(void);
	void update(void);

};

#endif /* CODE_SYSTEM_ROBOT_H_ */
