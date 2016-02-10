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
#include <util/atomic.h>
#include <math.h>

#define DEG_TO_RAD 0.017453293

class TranslativeStepper : public PrimitiveStepper {

private:
	//Conversion factors for 1mm of X/Y movement or 1 degree rotation into the amount of steps the robot has to do.
	float xFact, yFact, rFact;
	float yRCompensation;

	//Frequency difference between the ISR Update frequency and the Calculation Frequency.
	float ISRPerCal;

public:
	//Contstructor for a new Translative Stepper.
	//*PORT is a pointer to the port of the motor, pins the start of the pin (Step, then Dir)
	//ISRPerCal is the difference in frequencies of the stepper motor "update" function and the recalculation of X and Y movements.
	//"microstepping" is the microstepping value of the stepper motor
	//Radius is the wheel radius for the motor, rotation the Z-Axis rotation facing towards X-Movement, and distance the distance of the wheel to the center of the robot.
	TranslativeStepper(volatile uint8_t *PORT, uint8_t pins, float ISRPerCal, uint8_t microstepping, float radius, float rotation, float distance, float yRComp);

	//Move the motor by x and y mm, and rotate it by r degrees
	void stepBy(float x, float y, float r);
	//Move the motor by x and y mm
	void stepBy(float x, float y);
	//Rotate the robot by r degrees
	void stepBy(float r);
};

#endif /* CODE_TRANSLATIVESTEPPER_H_ */
