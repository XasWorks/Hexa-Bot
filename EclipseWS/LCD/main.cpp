/*
 * main.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: xasin
 */

#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "Code/LCD.h"
#include "PWMLed.h"

LCD disp(&PORTA);			//Create a new display object for the system.

PWMLed light1(&PORTD, 3, 20);
PWMLed light2(&PORTD, 0, 200);


volatile uint32_t ms=0;		//Millisecond-Counter variable.

volatile uint8_t pwm1 = 0;	//PWM Variable (contains counter and upper limit)
volatile uint8_t trg1 = 0;	//PWM "target" (to switch LED on and off)

volatile uint8_t splitter=0;	//Variable for the software prescaler for the interrupt.

ISR(TIMER1_COMPA_vect) {
	disp.updateDisplay();
	if(ms != 0)
		ms++;

	light1.updatePWM();
	light2.updatePWM();
}


int main() {
	PORTB |= (1<<0 | 1<<1);

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/1000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	disp.cursorMode(CURSOR_ON_BLINK);

	//State of the light. 0 means completely off, 1 means awake, 2 means asleep
	uint8_t lightState = 0;
	uint8_t oldPinState = PINB & (0b00000011);
	while(true) {
		if(oldPinState != (PINB & 0b00000011)) {
			oldPinState = PINB & 0b00000011;
			switch(lightState) {
			case 0:
				if((PINB & (1<<1)) == 0)
					lightState = 1;
			break;
			case 1:
				if((PINB & (1)) == 0) {
					light2.setPWM(10);
					light1.setPWM(0);

					if((PINB & (1<<1)) == 0) {
						lightState = 2;
						light2.setPWM(0);
					}
				}
				else {
					light2.setPWM(0);
					light1.setPWM(13);

					if((PINB & (1<<1)) == 0) {
						light1.setPWM(0);
						lightState = 0;
					}
				}
			break;

			case 2:
				if(((PINB & 1) != 0) || ((PINB & (1<<1)) == 0)) {
					lightState = 1;
				}
			}
		}
	}
}
