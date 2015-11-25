/*
 * Locomotor.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: xasin
 */

#include "Locomotor.h"
#include <util/delay.h>

Locomotor::Locomotor(TranslativeStepper *A, TranslativeStepper *B, TranslativeStepper *C, uint16_t ISRFreq) {
	this->A = A;
	this->B = B;
	this->C = C;

	this->ISRFreq = ISRFreq;

}

void Locomotor::recalculateXYFact() {
	float travelMM = sqrt(pow((this->xTarget - this->xPos), 2)
			+ pow(this->yTarget - this-> yPos, 2));

	this->xPerISR = ((this->xTarget - this->xPos) / travelMM) * this->speed / this->ISRFreq;
	this->yPerISR = ((this->yTarget - this->yPos) / travelMM) * this->speed / this->ISRFreq;
}

void Locomotor::setRotationSpeed(float newSpeed) {
	this->rPerISR = newSpeed / this->ISRFreq;
}

void Locomotor::setSpeed(float newSpeed) {
	this->speed = newSpeed;

	this->recalculateXYFact();
}

void Locomotor::moveTo(float x, float y) {
	this->xTarget = x;
	this->yTarget = y;

	this->recalculateXYFact();
}

void Locomotor::moveBy(float x, float y) {
	this->xTarget += x;
	this->yTarget += y;

	this->recalculateXYFact();
}

void Locomotor::moveTowards(float dist) {
	this->xTarget += dist * cos(this->rPos * DEG_TO_RAD);
	this->yTarget += dist * sin(this->rPos * DEG_TO_RAD);

	this->recalculateXYFact();
}

void Locomotor::moveTowards(float dist, float dir) {
	this->xTarget += dist * cos(dir * DEG_TO_RAD);
	this->yTarget += dist * sin(dir * DEG_TO_RAD);

	this->recalculateXYFact();
}

void bool Locomotor::isReady() {
	if(this->xTarget != this->xPos)
		return false;
	if(this->yTarget != this->yPos)
		return false;
	if(this->rTarget != this->rPos)
		return false;
	return true;
}

void Locomotor::flush() {
	while(this->isReady() == false) {
		_delay_ms(1);
	}
}

void Locomotor::update() {
	//Pre-Calculate the Sin and Cos values
	float cSin = sin(this->rPos * DEG_TO_RAD);
	float cCos = cos(this->rPos * DEG_TO_RAD);

	//Calculate the steps that the motors will have to do this calculation. CAUTION - X and Y Motor axis do not aling with the Robot's current X and Y Axis!
	float xDifference = this->xTarget - this->xPos;
	float yDifference = this->yTarget - this->yPos;
	float rDifference = this->rTarget - this->rPos;

	float xThisISR = 0;
	float yThisISR = 0;
	float rThisISR = 0;

	//X-Steps calculation
	if(xDifference != 0) {
		xThisISR = (fabs(xDifference) > fabs(this->xPerISR)) ? xPerISR : xDifference;
		this->xPos += xThisISR;
	}

	//Y-Steps calculation
	if(yDifference != 0) {
		yThisISR = (fabs(yDifference) > fabs(this->yPerISR)) ? yPerISR : yDifference;
		this->yPos += yThisISR;
	}

	float xRotated = cCos * xThisISR + cSin * yThisISR;
	float yRotated = cSin * xThisISR + cCos * yThisISR;

	//Rotation-Stepping calculation
	if(rDifference != 0) {
		rThisISR = (fabs(rDifference) > fabs(this->rPerISR)) ? this->rPerISR : rDifference;
		this->rPos += rThisISR;
	}

	A->stepBy(xRotated, yRotated, rThisISR);
	B->stepBy(xRotated, yRotated, rThisISR);
	C->stepBy(xRotated, yRotated, rThisISR);

}
