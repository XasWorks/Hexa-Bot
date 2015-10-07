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
	this->updateSpeed = upSp;

	this->stepsPerRotation = stepsPerRotation;

	*(PORT - 1) |= (3 << pin);
}

//Set the speed of the motor to the given amount of degrees/sec
void RotaryStepper::setSpeed(uint16_t degreePerSec) {
	this->stepSpeed = (uint16_t)(((((uint32_t)degreePerSec * (uint32_t)stepsPerRotation) / 360) << 15) / updateSpeed);
	//Calculate the required amount of steps per second. Shift left by 15 (sc) and then divide by ISR frequency
}

//Rotate the stepper to an absolute position in degrees.
void RotaryStepper::rotateTo(int32_t target) {
	stepsToGo = (target * (int32_t)stepsPerRotation)/360 - currentSteps;
	//Get the required steps it has to perform,
	//Then set the difference of current and wanted position into the toGo variable.
}

//Rotate the stepper to an absolute position in degrees with given software comma.
void RotaryStepper::rotateTo(int32_t target, uint8_t precision) {
	stepsToGo = ((target*stepsPerRotation)/360 >> precision)	- currentSteps;
	//Calculate the required amount of steps to do, divided by the software comma precision, then
	//Add the difference of current and wanted position to the toGo variable.
}

//Move the stepper motor by a relative amount.
void RotaryStepper::move(int32_t amount) {
	stepsToGo += ((amount*stepsPerRotation)/360);
	//Calculate the required amount of steps and add to the toGo variable.
}

//Move the stepper motor by a relative amount with given software comma.
void RotaryStepper::move(int32_t amount, uint8_t precision) {
	stepsToGo += ((amount*stepsPerRotation)/360 >> precision);
	//Calculate the required amount of steps to do divided by sc and then add to the toGo variable.
}
