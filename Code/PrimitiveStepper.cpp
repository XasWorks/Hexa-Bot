#include "PrimitiveStepper.h"

//Step the motor once into specified direction.
void PrimitiveStepper::step(uint8_t dir) {
	if (dir == 0) {					//Rotate it backwards
		*PORT |= (1 << (pin + 1));	//Reverse direction then step and reset.
		*PORT |= (1 << pin);
		*PORT &= ~(3 << pin);
		stepsToGo++;
		currentSteps--;
	} else {						//Rotate it forwards
		*PORT |= (1 << pin);
		*PORT &= ~(1 << pin);
		stepsToGo--;
		currentSteps++;
	}
}

//Constructor for the motor stepper. Takes in port pointer, pin and ISR frequency.
PrimitiveStepper::PrimitiveStepper(volatile uint8_t *P, uint8_t pin,
		uint16_t upSpeed) {
	this->PORT = P;
	this->pin = pin;
	this->updateSpeed = upSpeed;
	*(PORT - 1) |= (3 << pin);
}

//Default constructor for derived classes. Does nothing.
PrimitiveStepper::PrimitiveStepper() {
}

//ISR Routine for the motor, updates it when required.
void PrimitiveStepper::update() {
	if (stepsToGo != 0) {	//If there are any steps to do ..
		virtualSteps += stepSpeed;//Add up the stepping speed to the virtual steps ...
		if (virtualSteps >= (1 << 15)) {//If there has to be an actual step done
			virtualSteps -= (1 << 15);
			if (stepsToGo < 0) {		//If it has to move backwards
				step(0);
			} else {					//Otherwise, if it has to move forwards
				step(1);
			}

			if (stepsToGo == 0)	//If the goal was reached, reset the virtual steps.
				virtualSteps = 0;
		}
	}
}

//Set the speed of the motor in steps per second.
void PrimitiveStepper::setSpeed(uint16_t stepsPerSec) {
	stepSpeed = (uint16_t) (((uint32_t) (stepsPerSec) * (1 << 15))
			/ (uint32_t) updateSpeed);//Calculate the required steps per ISR call.
									  //Uses 15 bit software comma for extra precision.
}

//Move the stepper motor by the specified amount of steps.
void PrimitiveStepper::move(int32_t steps) {
	stepsToGo += steps;
}

//Wait for the motor movements to finish.
void PrimitiveStepper::flush() {
	while ((stepsToGo != 0) && (stepSpeed != 0)) {
	}

}

//Reset all the values back to 0, except PORT and PIN configurations.
void PrimitiveStepper::reset() {
	stepsToGo = 0;
	currentSteps = 0;
	virtualSteps = 0;
	stepSpeed = 0;
}
