/*
 * RotaryStepper.h
 *
 *  Created on: Oct 7, 2015
 *      Author: xasin
 */

#ifndef CODE_ROTARYSTEPPER_H_
#define CODE_ROTARYSTEPPER_H_

#include "PrimitiveStepper.h"

class RotaryStepper: public PrimitiveStepper {
private:
	//Config value for how many steps have to be done for a full rotation (Usually 200 * 2^x)
	int16_t stepsPerRotation;

public:
	//Constructor for the Rotary Motor class.
	//Requires a pointer to the PORT used, PIN, ISR SPEED and STEPS PER ROTATION
	RotaryStepper(volatile uint8_t *P, uint8_t pin, uint16_t updateFrequency,
			int16_t stepsPerRotation);

	//Returns the current position of the motor it is in.
	float getPosition();

	//Set the speed of the motor in degrees per second it should do.
	void setSpeed(float degreePerSec);

	//Rotate the motor to a specific, absolute position, given in degrees.
	//Optionally takes in a software comma for finer positioning.
	void rotateTo(float target);

	//Move the motor by the specified amount of degrees, relative to the current position.
	//Optionally takes in a software comma for finer positioning.
	void move(float amount);
	void move(int32_t amount, uint8_t precision);
};

#endif /* CODE_ROTARYSTEPPER_H_ */
