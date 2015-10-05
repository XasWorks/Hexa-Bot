/*
 * PWM.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: xasin
 */

#include "PWMLed.h"

	PWMLed::PWMLed(volatile uint8_t *P, uint8_t ledPin, uint8_t shiftingPrescaler) {
		PORT = P;
		pin = ledPin;
		*(PORT-1) |= (1<< pin);
		pwm = 0;
		pwmTrgt = 0;
		prscPWM = shiftingPrescaler;
		cPrscPWM = 0;
	}

	void PWMLed::setPWM(uint8_t n) {
		pwmTrgt = ((n) & (0x0f));
	}

	void PWMLed::updatePWM() {
		pwm = ((pwm +1) & 0x0f) | (pwm & 0xf0);
		if(((pwm & (0x0f)) == 0x0f) && ((pwm & (0xf0)) != 0)) {
			pwm &= ~(0x0f);
			*PORT |= (1<<pin);
		}
		if((pwm & (0x0f)) >= ((pwm & (0xf0)) >> 4)) {
			*PORT &= ~(1<<pin);
		}

		cPrscPWM++;
		if(cPrscPWM == prscPWM) {
			cPrscPWM = 0;
			if((pwmTrgt & (0x0f)) > ((pwm & (0xf0)) >> 4))
				pwm += (1<<4);
			if((pwmTrgt & (0x0f)) < ((pwm & (0xf0)) >> 4))
				pwm -= (1<<4);
		}
	}

