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
	float xSin = sin((globalRotation + localRotation) * DEG_TO_RAD) * X;
	float yCos = cos((globalRotation + localRotation) * DEG_TO_RAD) * Y;

	this->stepsToGo += (xSin + yCos) * stepsPerMM;
	this->stepSpeed = (stepsToGo * movementSpeed) / (xSin + yCos) / updateFrequency;
}

void DriveStepper::setSpeed(float mmPerSec) {
	this->movementSpeed = mmPerSec;
}
