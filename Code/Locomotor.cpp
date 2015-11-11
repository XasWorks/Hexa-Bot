/*
 * Locomotor.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: xasin
 */

#include "Locomotor.h"

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

void Locomotor::update() {
	float cSin = sin(this->rPos);
	float cCos = cos(this->rPos);
	float xThisISR = 0;
	if(fabs(this->xPos - this->xTarget) > this->xPerISR) {
		xThisISR = cSin * xPerISR + cCos* yPerISR;
		this->xPos += this->xPerISR;
	}
	float yThisISR = 0;
	if(fabs(this->yPos - this->yTarget) > this->yPerISR) {
		yThisISR = cCos* xPerISR + cSin * yPerISR;
		this->yPos += this->yPerISR;
	}

	A->stepBy(xThisISR, yThisISR);
	B->stepBy(xThisISR, yThisISR);
	C->stepBy(xThisISR, yThisISR);

}

