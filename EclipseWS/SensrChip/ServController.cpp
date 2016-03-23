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
	// TODO Auto-generated constructor stub

}

void ServController::endTransmission() {
	if(TWI_Handler::IO.buf.peek() == COMS_SERVO)
		setServo(TWI_Handler::IO.buf.peek(1));
}
