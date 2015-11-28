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

	this->xFact = ((this->xTarget - this->xPos) / travelMM);
	this->yFact = ((this->yTarget - this->yPos) / travelMM);
}

void Locomotor::setRotationSpeed(float newSpeed) {
	this->rPerISR = newSpeed / this->ISRFreq;
}

void Locomotor::setSpeed(float newSpeed) {
	if(newSpeed > 0) {
		this->speed = newSpeed / ISRFreq;
		this->speedTarget = newSpeed / ISRFreq;
	}
}

void Locomotor::setAcceleration(float acceleration) {
	if(acceleration > 0)
		this->acceleration = acceleration / ISRFreq;
}

void Locomotor::accelerateTo(float targetSpeed) {
	this->speedTarget = targetSpeed / ISRFreq;
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

bool Locomotor::isReady() {
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

void Locomotor::accelerate() {
	//Acceleration controls
	float speedDiff = speedTarget - speed;
	if(this->speedTarget > this->speed)
		this->speed += (this->acceleration > fabs(speedDiff)) ? speedDiff : this->acceleration;
	else if(this->speedTarget < this->speed)
		this->speed += (this->acceleration > fabs(speedDiff)) ? speedDiff : -this->acceleration;
}

void Locomotor::update() {

	accelerate();

	//Pre-Calculate the Sin and Cos values
	float cSin = sin(-1 * this->rPos * DEG_TO_RAD);
	float cCos = cos(-1 * this->rPos * DEG_TO_RAD);

	//Calculate the steps that the motors will have to do this calculation. CAUTION - X and Y Motor axis do not aling with the Robot's current X and Y Axis!
	float xDifference = this->xTarget - this->xPos;
	float yDifference = this->yTarget - this->yPos;
	float rDifference = this->rTarget - this->rPos;

	float xThisISR = 0;
	float yThisISR = 0;
	float rThisISR = 0;

	//X-Steps calculation
	if(xDifference != 0) {
		xThisISR = (fabs(xDifference) > fabs(this->xFact * speed)) ? xFact * speed : xDifference;
		this->xPos += xThisISR;
	}

	//Y-Steps calculation
	if(yDifference != 0) {
		yThisISR = (fabs(yDifference) > fabs(this->yFact * speed)) ? yFact * speed : yDifference;
		this->yPos += yThisISR;
	}

	float xRotated = cCos * xThisISR - cSin * yThisISR;
	float yRotated = cSin * xThisISR + cCos * yThisISR;

	//Rotation-Stepping calculation
	if(rDifference != 0) {
		rThisISR = (fabs(rDifference) > fabs(this->rPerISR)) ? ((rDifference < 0) ? -rPerISR : rPerISR) : rDifference;
		this->rPos += rThisISR;
	}

	A->stepBy(xRotated, yRotated, rThisISR);
	B->stepBy(xRotated, yRotated, rThisISR);
	C->stepBy(xRotated, yRotated, rThisISR);

}
