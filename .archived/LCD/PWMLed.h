/*
 * PWMLed.h
 *
 *  Created on: Oct 5, 2015
 *      Author: xasin
 */

#ifndef PWMLED_HPP_
#define PWMLED_HPP_

#include <avr/io.h>

class PWMLed {
private:
	volatile uint8_t pwm;
	volatile uint8_t pwmTrgt;
	volatile uint8_t *PORT;
	volatile uint8_t pin;
	volatile uint8_t prscPWM, cPrscPWM;

public:
	PWMLed(volatile uint8_t *P, uint8_t ledPin, uint8_t shiftingPrescaler);
	void setPWM(uint8_t n);
	void updatePWM();
};


#endif /* PWMLED_HPP_ */
