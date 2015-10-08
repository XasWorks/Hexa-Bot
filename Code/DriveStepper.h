/*
 * DriveStepper.h
 *
 *  Created on: 08.10.2015
 *      Author: xasin
 */

#ifndef CODE_DRIVESTEPPER_H_
#define CODE_DRIVESTEPPER_H_

#include "PrimitiveStepper.h"
#include <math.h>
#include <util/atomic.h>

#define DEG_TO_RAD 0.017453293

class DriveStepper: public PrimitiveStepper {
private:
	//Rotational offset of the motor.
	float localRotation;
	//Steps per MM of movement.
	float stepsPerMM;
	//Distance of the motor from the center of rotation.
	float motorOffset;

	//Rotation speed in Degrees / Second
	float rotationSpeed = 1;
	//Movement speed in mm / Second
	float movementSpeed;

	//Global rotation of the current motor (where it is facing)
	float globalRotation = 0;


public:
	DriveStepper(volatile uint8_t *P, uint8_t pin,
			uint16_t updateFrequency, float stepsPerMM, float motorOffset, float localRotation);

	void setSpeed(float mmPerSec);

	void moveXY(float X, float Y);
};

#endif /* CODE_DRIVESTEPPER_H_ */
