/*
 * ServController.cpp
 *
 *  Created on: Mar 18, 2016
 *      Author: xasin
 */

#include "ServController.h"


#define SERV_MIN 50
#define SERV_MAX 150

void setServo(uint8_t p) {
	OCR2A = SERV_MIN + (p * (SERV_MAX - SERV_MIN) / 255);
}

ServController::ServController() {
	// Initialisation of PWM Pin for the Servo
	DDRB |= (1 << PB3);

	TCCR2A = (1 << COM2A1 | 1 << WGM21 | 1 << WGM20);
	TCCR2B = (1 << CS22 | 1 << CS21);
}

void ServController::endTransmission() {
	if(TWI_Handler::IO.buf.peek() == COMS_SERVO)
		setServo(TWI_Handler::IO.buf.peek(1));
}
