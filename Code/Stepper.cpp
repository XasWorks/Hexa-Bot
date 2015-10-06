

#include "Stepper.h"


Stepper::Stepper(volatile uint8_t *P, uint8_t pin, uint16_t upSpeed) {
	this->PORT = P;
	this->pin = pin;
	this->updateSpeed = upSpeed;
	*(PORT -1) |= (3 << pin);
}

void Stepper::update() {
	if(stepsToGo != 0) {	//If there are any steps to do ..
		virtualSteps += stepSpeed;	//Add up the stepping speed to the virtual steps ...
		if((virtualSteps & (1<<15)) != 0) {	//If there has to be an actual step done
			virtualSteps &= ~(1<<15);
			if(stepsToGo < 0) {		//If it has to move backwards
				*PORT |= (1<<pin);
				*PORT &= ~(1<<pin);
				stepsToGo++;
			}
			else {					//Otherwise, if it has to move forwards
				*PORT |= (1<< (pin+1));
				*PORT |= (1<< pin);
				*PORT &= ~(3<< pin);
				stepsToGo--;
			}

			if(stepsToGo == 0)		//If the goal was reached, reset the virtual steps.
				virtualSteps = 0;
		}
	}
}

void Stepper::setSpeed(uint16_t stepsPerSec) {
	stepSpeed = (uint16_t)(((uint32_t)(stepsPerSec) * (32768)) / (uint32_t)updateSpeed);
}

void Stepper::move(int32_t steps) {
	stepsToGo += steps;
}

void Stepper::flush() {
	while((stepsToGo != 0)  && (stepSpeed != 0)) {}

}
