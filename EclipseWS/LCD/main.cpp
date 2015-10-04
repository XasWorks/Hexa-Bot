/*
 * main.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: xasin
 */

#include "/home/xasin/RoboNet/Code/LCD.cpp"
#include "PWMLed.cpp"

#include <avr/interrupt.h>
#include <math.h>

LCD disp(&PORTA);			//Create a new display object for the system.
PWMLed ligh(&PORTD, 0, 5);
PWMLed light(&PORTD, 2, 100);


volatile uint32_t ms=0;		//Millisecond-Counter variable.

volatile uint8_t pwm1 = 0;	//PWM Variable (contains counter and upper limit)
volatile uint8_t trg1 = 0;	//PWM "target" (to switch LED on and off)

volatile uint8_t splitter=0;	//Variable for the software prescaler for the interrupt.

ISR(TIMER1_COMPA_vect) {
	disp.updateDisplay();
	if(ms != 0)
		ms++;

	ligh.updatePWM();
	light.updatePWM();
}

void setPWM(uint8_t n) {
	trg1 = n;
}

int main() {
	DDRB |= (1<<4);

	DDRD |= (1<<0 | 1<<2);

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/1000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	disp.cursorMode(CURSOR_OFF);
	disp.writeString("Test!",0);
	disp.setCursor(16);

	uint8_t i=0;
	while(true) {
		light.setPWM(10);
		ligh.setPWM(0);
		_delay_ms(2000);
		light.setPWM(0);
		ligh.setPWM(10);
		_delay_ms(2000);
	}
}
