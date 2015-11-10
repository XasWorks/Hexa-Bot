/*
 * TranslativeStepper.h
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#ifndef CODE_TRANSLATIVESTEPPER_H_
#define CODE_TRANSLATIVESTEPPER_H_

#include "PrimitiveStepper.h"
#include <avr/io.h>
#include <math.h>

#define DEG_TO_RAD 0.017453293

class TranslativeStepper : public PrimitiveStepper {

private:
	//Coordinate factors for the motor (sin/cos precalculated and in steps/mm) aswell as the steps per degree factor
	volatile float xFact, yFact, sPerDeg;
	//How often will the ISR be called before the steps are recalculated?
	volatile uint8_t ISRPerCal;

public:
	//Contstructor for a new Translative Stepper.
	//*PORT is a pointer to the port of the motor, pins the start of the pin (Step, then Dir)
	//ISRPerCal is the difference in frequencies of the stepper motor "update" function and the recalculation of X and Y movements.
	//"microstepping" is the microstepping value of the stepper motor
	//Radius is the wheel radius for the motor, rotation the Z-Axis rotation facing towards X-Movement, and distance the distance of the wheel to the center of the robot.
	TranslativeStepper(volatile uint8_t *PORT, uint8_t pins, uint8_t ISRPerCal, uint8_t microstepping, float radius, float rotation, float distance);

	//Make the system recalculate values for movement along the x and y axis, or otherwise rotation.
	void stepBy(float x, float y);
	void stepBy(float r);
};

#endif /* CODE_TRANSLATIVESTEPPER_H_ */
