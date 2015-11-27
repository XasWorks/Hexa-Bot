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

#define DEG_TO_RAD 0.017453293

class Locomotor : public Movable {
private:
	//Stepper motor instances
	TranslativeStepper *A,*B,*C;

	//Distance that the motors have to cover per Calculation
	volatile float xFact = 0, yFact = 0, rPerISR = 0;
	volatile float speedTarget = 0, acceleration = 0;

	//Buffer values for sinus and cosin calculations
	volatile float cSin, cCos, oldAngle;

	//Speed at which the robot will recalculate
	uint16_t ISRFreq;

	void recalculateXYFact();

	void accelerate();
	void precalTrig();
	float calcAxis(float position, float target, float fact);

public:
	Locomotor(TranslativeStepper *A, TranslativeStepper *B, TranslativeStepper *C, uint16_t ISRSpeed);

	void setRotationSpeed(float newSpeed);
	void setSpeed(float speed);

	void setAcceleration(float acceleration);
	void accelerateTo(float targetSpeed);

	void moveTo(float x, float y);
	void moveBy(float x, float y);

	//Move the motor towards either specified direction or wanted heading
	void moveTowards(float dist);
	void moveTowards(float dist, float direction);

	bool isReady();
	void flush();

	void update();
};

#endif /* CODE_LOCOMOTOR_H_ */
