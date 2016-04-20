/*
 * BallFineGrab.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: xasin
 */

#include "BallFineGrab.h"

uint8_t BallFineGrab::getIRDist() {
	this->sensor->updateWaiting();
	return this->sensor->get_distance();
}

BallFineGrab::BallFineGrab(Robot *sys, IRDistanceSensor *sens) {
	this->system = sys;
	this->sensor = sens;
}

void BallFineGrab::execute() {
	Subspace mSpace = Subspace(&this->system->Motor);

	mSpace.setSpeed(100);
	mSpace.setRotationSpeed(100);

	mSpace.moveBy(-50,0);
	mSpace.flush();

	if(this->getIRDist() < 100) {
		while(this->getIRDist() < 100) {
			mSpace.moveBy(-1, 0);
			mSpace.flush();
		}
	}
}
