/*
 * Locomotor.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: xasin
 */

#include "Locomotor.h"
#include <util/delay.h>

//Constructor of the Locomotor object
Locomotor::Locomotor(TranslativeStepper *A, TranslativeStepper *B,
		TranslativeStepper *C, uint16_t ISRFreq) {
	this->A = A;
	this->B = B;
	this->C = C;

	this->ISRFreq = ISRFreq;

}

//Recalculate X and Y speed factors.
void Locomotor::recalculateXYFact() {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		float travelMM = sqrt(
				pow((this->xTarget - this->xPos), 2)
						+ pow(this->yTarget - this->yPos, 2)); //Calculate the distance the robot has to travel.

						//Calculate the X and Y factors (basically sinus and cosinus values for current direction of travel)
		this->xFact = ((this->xTarget - this->xPos) / travelMM);
		this->yFact = ((this->yTarget - this->yPos) / travelMM);
	}
}

void Locomotor::setRotationSpeed(float newSpeed) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->rPerISR = fabs(newSpeed) / this->ISRFreq;
	}
}

void Locomotor::setSpeed(float newSpeed) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		if (newSpeed > 1) {
			this->speedTarget = newSpeed / ISRFreq;
		}
	}
}

void Locomotor::setAcceleration(float acceleration) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		if (acceleration > 0)
			this->acceleration = acceleration / ISRFreq / ISRFreq;
	}
}

void Locomotor::moveTo(float x, float y) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->xTarget = x;
		this->yTarget = y;

		this->recalculateXYFact();
	}
}

void Locomotor::moveBy(float x, float y) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->xTarget += x;
		this->yTarget += y;

		this->recalculateXYFact();
	}
}

void Locomotor::moveTowards(float dist) {
		this->moveTowards(dist, this->rPos);
}

void Locomotor::moveTowards(float dist, float dir) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->xTarget += dist * cos(dir * DEG_TO_RAD);
		this->yTarget += dist * sin(dir * DEG_TO_RAD);

		this->recalculateXYFact();
	}
}

void Locomotor::flush() {
	do {
		_delay_ms(10);
	} while (!this->isReady());
}

void Locomotor::update() {

	//Pre-Calculate the Sin and Cos values for the current INVERSE Rotation!!
	float cSin = sin(-1 * this->rPos * DEG_TO_RAD);
	float cCos = cos(-1 * this->rPos * DEG_TO_RAD);

	//Calculate the steps that the motors will have to do this calculation. CAUTION - X and Y Motor axis do not aling with the Robot's current X and Y Axis!
	float xDifference = this->xTarget - this->xPos;
	float yDifference = this->yTarget - this->yPos;
	float rDifference = this->rTarget - this->rPos;
	float speedDiff = this->speedTarget - this->speed; //Calculate the speed difference (target to current speed)

	//How much will the robot have to move each calculation?
	float xThisISR = 0;
	float yThisISR = 0;
	float rThisISR = 0;

	/* --- Basic explanation of the calculation ---
	 * if the motor has to do any movement in the specified direction
	 * Calculate how much movement it will have to do in this ISR. This is either the currently set speed, calculated from the Axis-Speed-Factor and current robot speed,
	 * or the remaining distance between target and current position, whatever is smaller.
	 * Then increase (or decrease) the current position by the amount of mm that the robot will move this ISR.
	 */

	//Speed recalcultion
	if (speedDiff != 0)
		this->speed += (
				(fabs(speedDiff) > this->acceleration) ?
						((speedDiff > 0) ?
								this->acceleration : -this->acceleration) :
						speedDiff);

	//X-Steps calculation
	if (xDifference != 0) {
		xThisISR =
				(fabs(xDifference) > fabs(this->xFact * speed)) ?
						xFact * speed : xDifference;
		this->xPos += xThisISR;
	}

	//Y-Steps calculation
	if (yDifference != 0) {
		yThisISR =
				(fabs(yDifference) > fabs(this->yFact * speed)) ?
						yFact * speed : yDifference;
		this->yPos += yThisISR;
	}

	//Rotation-Stepping calculation
	if (rDifference != 0) {
		rThisISR =
				(fabs(rDifference) > fabs(this->rPerISR)) ?
						((rDifference < 0) ? -rPerISR : rPerISR) : rDifference;
		this->rPos += rThisISR;
	}

	//Rotate the movement axis.
	//As mentioned before, this is due to the ROBOT AXIS != MOTOR-RELATIVE AXIS
	float xRotated = cCos * xThisISR - cSin * yThisISR;
	float yRotated = cSin * xThisISR + cCos * yThisISR;

	A->stepBy(xRotated, yRotated, rThisISR);
	B->stepBy(xRotated, yRotated, rThisISR);
	C->stepBy(xRotated, yRotated, rThisISR);

	//Reset acceleration if at target and not having received a new command for ACCEL_DEBOUNCE_CYCLES updates
	if (this->atPosition()) {
		if (accelDebounce == 0)
			this->speed = 0;
		else
			accelDebounce--;
	} else
		accelDebounce = ACCEL_DEBOUNCE_CYCLES;

	//Make sure the rotation values do not get too high
	if (this->rPos > 360) {
		this->rPos -= 360;
		this->rTarget -= 360;
	}
	else if(this->rPos < -360) {
		this->rPos += 360;
		this->rTarget += 360;
	}
}
