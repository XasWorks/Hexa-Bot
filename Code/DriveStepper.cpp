/*
 * DriveStepper.cpp
 *
 *  Created on: 08.10.2015
 *      Author: xasin
 */

#include "DriveStepper.h"

DriveStepper::DriveStepper(volatile uint8_t *P, uint8_t pin,
		uint16_t updateFrequency, uint16_t calculationFrequency,
		float stepsPerMM, float motorOffset, float localRotation) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->PORT = P;
		this->pin = pin;
		this->updateFrequency = updateFrequency;
		this->ISRPerCal = updateFrequency / calculationFrequency;

		*(PORT - 1) |= (3 << pin);

		this->stepsPerMM = stepsPerMM;
		this->motorOffset = motorOffset;
		this->localRotation = localRotation;

		currentRotation = 0;
		currentX = 0;
		currentY = 0;

		calculationDivider = 0;
	}
}

void DriveStepper::recalculate() {
	if (++calculationDivider == ISRPerCal) {
		calculationDivider = 0;

		if (fabs(targetX - currentX) >= fabs(xPerCal)) {
			currentX += xPerCal;

			stepsToGo += sin((currentRotation + localRotation) * DEG_TO_RAD)
					* xPerCal * stepsPerMM;
		}

		if (fabs(targetY - currentY) >= fabs(yPerCal)) {
			currentY += yPerCal;

			stepsToGo += cos((currentRotation + localRotation) * DEG_TO_RAD)
					* yPerCal * stepsPerMM;
		}

		stepSpeed = fabs(stepsToGo / (ISRPerCal));
	}
	else if(calculationDivider == ISRPerCal /2) {

		if(fabs(targetRotation - currentRotation) >= fabs(degPerCal)) {
			if((targetRotation - currentRotation) < 0) {
				currentRotation -= degPerCal;

				stepsToGo -= motorOffset*(degPerCal * DEG_TO_RAD) * stepsPerMM;
			}
			else {
				currentRotation += degPerCal;

				stepsToGo += motorOffset*(degPerCal * DEG_TO_RAD) * stepsPerMM;
			}
		}

		stepSpeed = fabs(stepsToGo / (ISRPerCal));
	}
}

void DriveStepper::moveXY(float X, float Y) {
	float totalMM = sqrt(pow(X, 2) + pow(Y, 2));

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		targetX += X;
		targetY += Y;
		xPerCal = X / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
		yPerCal = Y / ((totalMM / mmPerSec) * (updateFrequency / ISRPerCal));
	}
}

void DriveStepper::rotate(float angle) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		this->targetRotation += angle;
	}
}

void DriveStepper::setRotationSpeed(float degPerSec) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		this->degPerCal = degPerSec / (updateFrequency / ISRPerCal);
	}
}

void DriveStepper::setMovementSpeed(float mmPerSec) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->mmPerSec = mmPerSec;
	}
}
