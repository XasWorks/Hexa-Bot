/*
 * DriveStepper.cpp
 *
 *  Created on: 08.10.2015
 *      Author: xasin
 */

#include "DriveStepper.h"

DriveStepper::DriveStepper(volatile uint8_t *P, uint8_t pin,
		uint16_t updateFrequency, float stepsPerMM, float motorOffset, float localRotation) {
	this->PORT = P;
	this->pin = pin;
	this->updateFrequency = updateFrequency;
	*(PORT - 1) |= (3 << pin);

	this->stepsPerMM = stepsPerMM;
	this->motorOffset = motorOffset;
	this->localRotation = localRotation;
}


void DriveStepper::moveXY(float X, float Y) {
	float mmToMove = sin((globalRotation + localRotation) * DEG_TO_RAD) * X + cos((globalRotation + localRotation) * DEG_TO_RAD) * Y;

	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		this->stepsToGo = (mmToMove * stepsPerMM);
		this->stepSpeed =  fabs((stepsToGo * movementSpeed) / sqrt(pow(X,2) + pow(Y,2)));
	}
}

void DriveStepper::setSpeed(float mmPerSec) {
	this->movementSpeed = mmPerSec / updateFrequency;
}
