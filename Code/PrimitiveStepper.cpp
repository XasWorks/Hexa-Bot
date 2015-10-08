#include <util/delay.h>

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
	this->updateFrequency = upSpeed;
	*(PORT - 1) |= (3 << pin);
}

//Default constructor for derived classes. Does nothing.
PrimitiveStepper::PrimitiveStepper() {
}

//ISR Routine for the motor, updates it when required.
void PrimitiveStepper::update() {
	if ((stepsToGo <= -1) || (stepsToGo >= 1)) {	//If there are any steps to do ..

		stepBuffer += stepSpeed;	//Add up the stepping speed to the virtual steps ...

		if (stepBuffer >= 1) {		//If there has to be an actual step done
			stepBuffer -= 1;

			if (stepsToGo <= -1)		//If it has to move backwards
				step(0);
			else if(stepsToGo >= 1)				//Otherwise, if it has to move forwards
				step(1);

			if (stepsToGo == 0)		//If the goal was reached, reset the virtual steps.
				stepBuffer = 0;
		}
	}
}

//Set the speed of the motor in steps per second.
void PrimitiveStepper::setSpeed(uint16_t stepsPerSec) {
	stepSpeed = stepsPerSec / updateFrequency;//Calculate the required steps per ISR call.
}

//Move the stepper motor by the specified amount of steps.
void PrimitiveStepper::move(int32_t steps) {
	stepsToGo += steps;
}

//Wait for the motor movements to finish.
void PrimitiveStepper::flush() {
	while ((stepsToGo != 0) && (stepSpeed != 0)) {
		_delay_ms(1);
	}
}

//Reset all the values back to 0, except PORT and PIN configurations.
void PrimitiveStepper::reset() {
	stepsToGo = 0;
	currentSteps = 0;
	stepBuffer = 0;
	stepSpeed = 0;
}
