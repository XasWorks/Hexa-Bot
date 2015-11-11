/*
 * Locomotor.h
 *
 *  Created on: Nov 11, 2015
 *      Author: xasin
 */

#ifndef CODE_LOCOMOTOR_H_
#define CODE_LOCOMOTOR_H_

#include <math.h>
#include "Movable.h"
#include "TranslativeStepper.h"

class Locomotor : public Movable {
private:
	//Stepper motor instances
	TranslativeStepper *A,*B,*C;

	//Distance that the motors have to cover per Calculation
	volatile float xPerISR, yPerISR, rPerISR;

	//Speed at which the robot will recalculate
	uint16_t ISRFreq;


public:
	Locomotor(TranslativeStepper *A, TranslativeStepper *B, TranslativeStepper *C, uint16_t ISRSpeed);

	void recalculateXYFact();

	void setRotationSpeed(float newSpeed);
	void setSpeed(float speed);

	void moveTo(float x, float y);
	void moveBy(float x, float y);

	void update();
};

#endif /* CODE_LOCOMOTOR_H_ */
