/*
 * DriveStepper.cpp
 *
 *  Created on: 08.10.2015
 *      Author: xasin
 */

#include "DriveStepper.h"
#include <util/delay.h>

DriveStepper::DriveStepper(volatile uint8_t *P, uint8_t pin,
		uint16_t updateFrequency, uint16_t calculationFrequency,
		float stepsPerMM, float motorOffset, float localRotation) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		//Initialize all the values.
		this->PORT = P;
		this->pin = pin;
		this->updateFrequency = updateFrequency;
		this->ISRPerCal = updateFrequency / calculationFrequency;
		this->stepsPerMM = stepsPerMM;
		this->motorOffset = motorOffset;
		this->localRotation = localRotation;

		//Enable output mode
		*(PORT - 1) |= (0b11 << pin);

		//Set absolute position values to 0.
		currentRotation = 0;
		currentX = 0;
		currentY = 0;

		//Set the software prescaler value to 0.
		calculationDivider = 0;
	}
}

void DriveStepper::recalSinCos(float angle) {
	if (angle != oldAngle) {
		currentSin = sin(angle);
		currentCos = cos(angle);

		oldAngle = angle;
	}
}

void DriveStepper::recalculate() {
	//Software prescaler
	if (++calculationDivider == ISRPerCal) {
		calculationDivider = 0;

		if (currentX != targetX) {
			if (fabs(targetX - currentX) >= fabs(xPerCal)) {
				recalSinCos((currentRotation + localRotation) * DEG_TO_RAD);

				/*//Step the motor by the according amount.*/
				stepsToGo += currentSin * xPerCal * stepsPerMM;

				//Shift the current position by what we will move.
				currentX += xPerCal;
			} else {
				stepsToGo += currentSin * (targetX - currentX) * stepsPerMM;

				currentX = targetX;
			}
		}

		if (currentY != targetY) {
			recalSinCos((currentRotation + localRotation) * DEG_TO_RAD);
			if (fabs(targetY - currentY) >= fabs(yPerCal)) {

				stepsToGo += currentCos * yPerCal * stepsPerMM;

				currentY += yPerCal;
			} else {
				stepsToGo += currentCos * (targetY - currentY) * stepsPerMM;

				currentY = targetY;
			}
		}

		stepSpeed = fabs(stepsToGo / (ISRPerCal));
	} else if (calculationDivider == ISRPerCal / 2) {

		if (fabs(targetRotation - currentRotation) >= fabs(degPerCal)) {
			if ((targetRotation - currentRotation) < 0) {
				currentRotation -= degPerCal;

				stepsToGo -= motorOffset * (degPerCal * DEG_TO_RAD)
						* stepsPerMM;
			} else {
				currentRotation += degPerCal;

				stepsToGo += motorOffset * (degPerCal * DEG_TO_RAD)
						* stepsPerMM;
			}
		}

		stepSpeed = fabs(stepsToGo / (ISRPerCal));
	}
}

void DriveStepper::moveXYBy(float X, float Y) {
	float totalMM = sqrt(pow(X, 2) + pow(Y, 2));

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		targetX += X;
		targetY += Y;
		xPerCal = X / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
		yPerCal = Y / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
	}
}

void DriveStepper::moveXYTo(float X, float Y) {
	float totalMM = sqrt(pow((currentX - X), 2) + pow(currentY - Y, 2));

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		targetX = X;
		targetY = Y;
		xPerCal = X / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
		yPerCal = Y / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
	}
}

void DriveStepper::rotateTo(float angle) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->targetRotation = angle;
	}
}

void DriveStepper::rotateBy(float angle) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->targetRotation += angle;
	}
}

void DriveStepper::finishRotation() {
	while ((currentRotation - targetRotation) != 0) {
		_delay_ms(1);
	}
}

void DriveStepper::finishMovement() {
	while ((currentX - targetX) != 0 || (currentY - targetY) != 0) {
		_delay_ms(1);
	}
}

void DriveStepper::finishAll() {
	finishMovement();
	finishRotation();
}

void DriveStepper::setRotationSpeed(float degPerSec) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->degPerCal = degPerSec / (updateFrequency / ISRPerCal);
	}
}

void DriveStepper::setMovementSpeed(float mmPerSec) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->mmPerSec = mmPerSec;
	}
}
