/*
 * PWM.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: xasin
 */

#include <avr/io.h>

class PWMLed {
private:
	volatile uint8_t pwm;
	volatile uint8_t pwmTrgt;
	volatile uint8_t *PORT;
	volatile uint8_t pin;
	volatile uint8_t prscPWM, cPrscPWM;

public:
	PWMLed(volatile uint8_t *P, uint8_t ledPin, uint8_t shiftingPrescaler) {
		PORT = P;
		*(PORT -1) |= (1<< pin);
		pin = ledPin;
		pwm = 0;
		pwmTrgt = 0;
		prscPWM = shiftingPrescaler;
		cPrscPWM = 0;
	}

	void setPWM(uint8_t n) {
		pwmTrgt = ((n) & (0x0f));
	}

	void updatePWM() {
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
};

