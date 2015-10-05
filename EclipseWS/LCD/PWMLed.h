/*
 * PWMLed.h
 *
 *  Created on: Oct 5, 2015
 *      Author: xasin
 */

#ifndef PWMLED_HPP_
#define PWMLED_HPP_

class PWMLed {
public:
	PWMLed(volatile uint8_t *P, uint8_t ledPin, uint8_t shiftingPrescaler);
	void setPWM(uint8_t n);
	void updatePWM();
};


#endif /* PWMLED_HPP_ */
