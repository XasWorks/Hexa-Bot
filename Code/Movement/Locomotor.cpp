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
	float travelMM = sqrt(pow((this->xPos - this->xTarget), 2)
			+ pow(this->xPos - this-> yTarget, 2));

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

void Locomotor::update() {
	//Pre-Calculate the Sin and Cos values
	float cSin = sin(this->rPos);
	float cCos = cos(this->rPos);

	//Calculate the steps that the motors will have to do this calculation. CAUTION - X and Y Motor axis do not aling with the Robot's current X and Y Axis!
	float xDifference = this->xTarget - this->xPos;
	float yDifference = this->yTarget - this->yPos;
	float rDifference = this->rTarget - this->rPos;

	float xThisISR = 0;
	float yThisISR = 0;
	float rThisISR = 0;


	//TODO implement a different, separate calculation of "*** This ISR"

	//X-Steps calculation
	if(xDifference != 0) {
		if(fabs(xDifference) > this->xPerISR) {
			xThisISR = cSin * xPerISR + cCos* yPerISR;
			this->xPos += this->xPerISR;
		}
		else {
			xThisISR = cSin * xDifference + cCos * yDifference;
			this->xPos = this->xTarget;
		}
	}

	//Y-Steps calculation
	if(yDifference != 0) {
		if(fabs(yDifference) > this->yPerISR) {
			yThisISR = cCos* xPerISR + cSin * yPerISR;
			this->yPos += this->yPerISR;
		}
		else {
			yThisISR = cCos * xDifference + cSin * yDifference;
			this->yPos = this->yTarget;
		}
	}

	//Rotation-Stepping calculation
	if(rDifference != 0) {
		if(fabs(rDifference) > this->rPerISR) {
			rThisISR = this->rPerISR;
			this->rPos += this->rPerISR;
		}
		else {
			rThisISR = rDifference;
			this->rPos = this->rTarget;
		}
	}

	A->stepBy(xThisISR, yThisISR, rThisISR);
	B->stepBy(xThisISR, yThisISR, rThisISR);
	C->stepBy(xThisISR, yThisISR, rThisISR);

}
