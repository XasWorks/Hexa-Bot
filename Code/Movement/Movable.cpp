/*
 * Movable.cpp
 *
 *  Created on: 10.11.2015
 *      Author: xasin
 */

#include "Movable.h"

Movable::Movable() {
	xPos = 0;
	xTarget = 0;

	yPos = 0;
	yTarget = 0;

	speed = 0;

	rPos = 0;
	rTarget = 0;
	rSpeed = 0;
}


void Movable::setRotationSpeed(float newSpeed) {
	rSpeed = newSpeed;
}

void Movable::setSpeed(float newSpeed) {
	speed = newSpeed;
}


void Movable::rotateTo(float angle) {
	rTarget = angle;
}

void Movable::headTo(float angle) {
	//First, calculate the current heading (by using Modulo of a full rotation). Then subtract to be left with the angle the robot has to rotate to get to the specific heading
	//rTarget -= (r) - angle;  TODO Fix calculation
}

void Movable::rotateBy(float angle) {
	rTarget += angle;
}


void Movable::moveTo(float x, float y) {
	xTarget = x;
	yTarget = y;
}

void Movable::moveBy(float x, float y) {
	xTarget += x;
	yTarget += y;
}

bool Movable::isReady() {
	return (this->atPosition() && this->atRotation());
}

bool Movable::atRotation() {
	if(this->rTarget == this->rPos)
		return true;
	return false;
}
bool Movable::atPosition() {
	if((this->xTarget == this->xPos) && (this->yTarget == this->yPos))
		return true;
	return false;
}

float Movable::getX() {
	return xPos;
}

float Movable::getY() {
	return yPos;
}

float Movable::getR() {
	return rPos;
}
