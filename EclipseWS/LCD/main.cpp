/*
 * main.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: xasin
 */

#include "/home/xasin/RoboNet/Code/LCD.cpp"
#include <avr/interrupt.h>


LCD disp(&PORTA);

ISR(TIMER1_COMPA_vect) {
	disp.updateDisplay();
}

int main() {
	DDRB |= (1<<4);

	TCCR1A |= (1<< WGM11);
	TCCR1B |= ((1<< CS11) | (1<< CS10));
	OCR1A =	F_CPU/64/1000 -1;

	TIMSK1 |= (1<< OCIE1A);

	sei();

	disp.cursorMode(CURSOR_ON_BLINK);
	disp.writeString("Test!",0);
	disp.setCursor(16);

	uint8_t i=0;
	while(true) {
		_delay_ms(100);
		disp.writeNum(i++,16,3);
	}
}
