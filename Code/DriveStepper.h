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
	uint16_t ISRPerCal;
	uint16_t calculationDivider;

	//Rotational offset of the motor.
	volatile float localRotation;
	//Steps per MM of movement.
	volatile float stepsPerMM;
	//Distance of the motor from the center of rotation.
	volatile float motorOffset;

	//Movement speed in mm / Sec
	volatile float mmPerSec;

	//Current position of the robot (in mm or degrees)
	volatile float currentX;
	volatile float currentY;
	volatile float currentRotation;

	//Target positions of the robot (in mm or degrees)
	volatile float targetX;
	volatile float targetY;
	volatile float targetRotation;

	//Buffer values of the subroutine calculation.
	volatile float xPerCal;
	volatile float yPerCal;
	volatile float degPerCal;

	//Buffer values for the buffered triangulation calculations
	volatile float oldAngle;
	volatile float currentSin;
	volatile float currentCos;

	//Sinus and Cosinus calculation with buffers (Quicker processing)
	void recalSinCos(float angle);


public:
	//Constructor for one of the driver stepper motors.
	//Requires:PORT Pointer, ISR frequency, recalculationFrequency, steps per MM, radius of the motor and the local rotation.
	DriveStepper(volatile uint8_t *P, uint8_t pin,
			uint16_t updateFrequency, uint16_t calculationFrequency, float stepsPerMM, float motorOffset, float localRotation);

	//Recalculation ISR. Call together with the normal update after setting sei();
	void recalculate();

	//Set the movement speed in mm per second.
	void setMovementSpeed(float mmPerSec);
	//Set the rotational speed in degrees per second.
	void setRotationSpeed(float degPerSec);

	//Rotate the motor by a given angle in degrees
	void rotate(float angle);
	//Move the robot by the given mm in A and Y.
	void moveXY(float X, float Y);
};

#endif /* CODE_DRIVESTEPPER_H_ */
