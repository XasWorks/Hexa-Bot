/*
 * LF3Sens.cpp
 *
 *  Created on: Jan 3, 2016
 *      Author: xasin
 */

#include "LF3Sens.h"

LF3Sens::LF3Sens() {
}

//Decide on the next status of the outputs
void LF3Sens::setStatus(uint8_t sensors) {
	switch(sensors) {
	case 0:
		this->lineStatus = LF_LOST;
	break;

	case 0b100:
		this->lineOffset = LF_LEFT;
	break;

	case 0b110:
		this->lineStatus = LF_OK;
		this->lineOffset = LF_LEFT / 2;
	break;

	case 0b010:
		this->lineStatus = LF_OK;
		this->lineOffset = 0;
	break;

	case 0b011:
		this->lineStatus = LF_OK;
		this->lineOffset = LF_RIGHT / 2;
	break;

	case 0b001:
		this->lineOffset = LF_RIGHT;
	break;

	case 0b111:
		this->lineStatus = LF_INTSEC;
		if(this->lineOffset == 0)
			this->lineOffset = INTSEC_DEFAULT_DIR;
	break;

	default:
		this->lineStatus = LF_AMBIG;
	break;
	}
}

//Update the output values
void LF3Sens::update() {

	//The sensor outputs give "0" when they are on a line, thusly the inputs have to be inverted
	uint8_t sensors = ~((PINC & 0b111) | 0b11111000 );

	//Check if the sensors have changed. If so, wait for DELAY_VAL Cycles (Debuffing)
	if(sensors != oSens) {
		oSens = sensors;
		uDelay = DELAY_VAL;
	}
	//If the sensors have not changed for a while, update them.
	else if(uDelay == 0)
		setStatus(sensors);
	//Count down.
	else
		uDelay--;
}
