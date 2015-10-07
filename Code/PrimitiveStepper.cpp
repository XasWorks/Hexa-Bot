
#include "PrimitiveStepper.h"

void PrimitiveStepper::step(uint8_t dir) {
	if (dir == 0) {
		*PORT |= (1 << (pin + 1));
		*PORT |= (1 << pin);
		*PORT &= ~(3 << pin);
		stepsToGo--;
		totalSteps--;
	} else {
		*PORT |= (1 << pin);
		*PORT &= ~(1 << pin);
		stepsToGo++;
		totalSteps++;
	}
}

PrimitiveStepper::PrimitiveStepper(volatile uint8_t *P, uint8_t pin,
		uint16_t upSpeed) {
	this->PORT = P;
	this->pin = pin;
	this->updateSpeed = upSpeed;
	*(PORT - 1) |= (3 << pin);
}

void PrimitiveStepper::update() {
	if (stepsToGo != 0) {	//If there are any steps to do ..
		virtualSteps += stepSpeed;//Add up the stepping speed to the virtual steps ...
		if ((virtualSteps & (1 << 15)) != 0) {//If there has to be an actual step done
			virtualSteps &= ~(1 << 15);
			if (stepsToGo < 0) {		//If it has to move backwards
				step(1);
			} else {					//Otherwise, if it has to move forwards
				step(0);
			}

			if (stepsToGo == 0)	//If the goal was reached, reset the virtual steps.
				virtualSteps = 0;
		}
	}
}

void PrimitiveStepper::setSpeed(uint16_t stepsPerSec) {
	stepSpeed = (uint16_t) (((uint32_t) (stepsPerSec) * (32768))
			/ (uint32_t) updateSpeed);
}

void PrimitiveStepper::move(int32_t steps) {
	stepsToGo += steps;
}

void PrimitiveStepper::flush() {
	while ((stepsToGo != 0) && (stepSpeed != 0)) {
	}

}

void PrimitiveStepper::reset() {
	stepsToGo = 0;
	totalSteps = 0;
	virtualSteps = 0;
	stepSpeed = 0;
}
