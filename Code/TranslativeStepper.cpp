/*
 * TranslativeStepper.cpp
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#include "TranslativeStepper.h"

TranslativeStepper::TranslativeStepper(volatile uint8_t *PORT, uint8_t pins, uint8_t ISRPerCal, uint8_t microstepping, float radius, float rotation, float distance) {
	this->PORT = PORT;
	this->pin = pin;
	this->ISRPerCal = ISRPerCal;

	*(PORT - 1) |= (0b11 << pin);

	float stepsPerMM = (M_PI * 2 * radius) / (200 * microstepping);

	float xFact = stepsPerMM * sin(rotation);
	float yFact = stepsPerMM * cos(rotation);
	float sPerDeg = (M_PI * 0.0055555555555 * distance) / stepsPerMM;
}

void TranslativeStepper::stepBy(float x, float y) {
	//Calculate the steps to go by multiplying X and Y movement (in mm)
	//with the according factors (given in steps/MM)
	stepsToGo += x * xFact + y * yFact;
	stepSpeed = stepsToGo / ISRPerCal;
}

void TranslativeStepper::stepBy(float r) {
	//Calculate the steps to go by multiplying the rotation to do (in degrees)
	//with the steps / degrees precalculated value
	stepsToGo += r * sPerDeg;
	stepSpeed = stepsToGo / ISRPerCal;
}
