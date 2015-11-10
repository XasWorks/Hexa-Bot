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
	rTarget -= (rTarget % 360) - angle;
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


float Movable::getX() {
	return xPos;
}

float Movable::getY() {
	return yPos;
}

float Movable::getR() {
	return rPos;
}
