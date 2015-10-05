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

LCD disp(&PORTA,&DDRA,&PINA);			//Create a new display object for the system.
PWMLed ligh(&PORTD, 0, 20);
PWMLed light(&PORTD, 2, 80);


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

int main() {
	DDRB |= (1<<4);

	DDRD |= (1<<2);

	TCCR1B |= ((1<< CS11) | (1<< CS10) | (1<< WGM12));
	OCR1A =	F_CPU/64/1000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	disp.cursorMode(CURSOR_OFF);

	while(true) {
		light.setPWM(10);
		ligh.setPWM(0);
		_delay_ms(2000);
		light.setPWM(0);
		ligh.setPWM(8);
		_delay_ms(800);
	}
}
