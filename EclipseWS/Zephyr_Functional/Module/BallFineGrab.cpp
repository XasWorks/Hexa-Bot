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

BallFineGrab::BallFineGrab(Robot *sys, IRDistanceSensor *sens, ServoController *serv) {
	this->system = sys;
	this->sensor = sens;
	this->servo = serv;
}

void BallFineGrab::execute() {
	Subspace mSpace = Subspace(&this->system->Motor);

	mSpace.setSpeed(100);
	mSpace.setRotationSpeed(100);

	// Raise the arm
	this->servo->setServo(255);

	// Move the robot backwards until the ball isn't in focus any more
	while(this->getIRDist() < GROUND_DISTANCE) {
		mSpace.moveBy(-1, 0);
		mSpace.flush();
	}

	// Move the robot to the middle of the ball
	mSpace.moveBy(25, 0);
	mSpace.flush();

	// Break if there isn't any ball there
	if(this->getIRDist() >= GROUND_DISTANCE)
		return;

	// Get close to the ball, but not too close

	uint8_t distVal = this->getIRDist();
	mSpace.rotateBy(-60);
	mSpace.flush();
	mSpace.moveBy(0, distVal - BALL_CLOSE_DISTANCE);
	mSpace.flush();


	mSpace.rotateBy(60);
	mSpace.flush();

	// Lower the servo
	this->servo->setServo(0);
	_delay_ms(300);

	// Aaaannndd kick the ball because we are too lazy to do it properly :P
	mSpace.setRotationSpeed(30);
	mSpace.rotateBy(-60);
	mSpace.flush();

	// Grab the ball up and lift it somewhat carefully
	_delay_ms(500);
	this->servo->setServo(50);
	_delay_ms(500);
	this->servo->setServo(255);

	// Return to original coordinates
	mSpace.moveBy(0, -mSpace.getY());
	mSpace.flush();
	mSpace.rotateTo(0);
	mSpace.flush();
	mSpace.moveTo(0, 0);
	mSpace.flush();
}
