/*
 * LF3Sens.cpp
 *
 *  Created on: Jan 3, 2016
 *      Author: xasin
 */

#include "LF3Sens.h"

LF3Sens::LF3Sens() {
	//Initialize the port inputs
	PORTC |= (0b111);
}

void LF3Sens::update() {
	uint8_t sensors = ~((PINC & 0b111) | 0b11111000 );

	switch(sensors) {
	case 0:
		this->lineStatus = LF_LOST;
	break;

	case 0b100:
		this->lineStatus = LF_OK;
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
		this->lineStatus = LF_OK;
		this->lineOffset = LF_RIGHT;
	break;

	default:
		this->lineStatus = LF_AMBIG;
	break;
	}
}
