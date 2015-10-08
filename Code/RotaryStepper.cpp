/*
 *
 *  * RotaryStepper.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: xasin
 */

#include "RotaryStepper.h"

//Constructor of the stepper motor.
//Takes in PORT Pointer, PIN, ISR Frequency and Steps/Rotation
RotaryStepper::RotaryStepper(volatile uint8_t *P, uint8_t pinMotor,
		uint16_t upSp, int16_t stepsPerRotation) {
	this->PORT = P;
	this->pin = pinMotor;
	this->updateFrequency = upSp;

	this->stepsPerRotation = stepsPerRotation;

	*(PORT - 1) |= (3 << pin);
}

//Set the speed of the motor to the given amount of degrees/sec
void RotaryStepper::setSpeed(float degreePerSec) {
	stepSpeed = (degreePerSec * stepsPerRotation) / 360 / updateFrequency;
	//Calculate the required amount of steps per second. Shift left by 15 (sc) and then divide by ISR frequency
}

float RotaryStepper::getPosition() {
	return ((float)currentSteps / stepsPerRotation) / 360;
}

//Rotate the stepper to an absolute position in degrees.
void RotaryStepper::rotateTo(float target) {
	stepsToGo = (target * stepsPerRotation)/360 - currentSteps;
	//Get the required steps it has to perform,
	//Then set the difference of current and wanted position into the toGo variable.
}

//Move the stepper motor by a relative amount.
void RotaryStepper::move(float amount) {
	stepsToGo += (amount * stepsPerRotation)/360;
	//Calculate the required amount of steps and add to the toGo variable.
}

//Move the stepper motor by a relative amount with given software comma.
void RotaryStepper::move(int32_t amount, uint8_t precision) {
	stepsToGo += ((amount*stepsPerRotation)/360 >> precision);
	//Calculate the required amount of steps to do divided by sc and then add to the toGo variable.
}
