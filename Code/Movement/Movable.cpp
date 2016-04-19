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
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		rSpeed = newSpeed;
	}
}

void Movable::setSpeed(float newSpeed) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		speed = newSpeed;
	}
}


void Movable::rotateTo(float angle) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		rTarget = angle;
	}
}

void Movable::rotateBy(float angle) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		rTarget += angle;
	}
}


void Movable::moveTo(float x, float y) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		xTarget = x;
		yTarget = y;
	}
}

void Movable::moveBy(float x, float y) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		xTarget += x;
		yTarget += y;
	}
}

bool Movable::atRotation() {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		return (round(this->rPos - this->rTarget) == 0);
	}
}

bool Movable::atPosition() {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		return (round(this->xPos - this->xTarget) == 0 && round(this->yPos - this->yTarget) == 0);
	}
}

bool Movable::isReady() {
	return (this->atPosition() & this->atRotation());
}

void Movable::flush() {
	while(!this->isReady()) {
	}
}

void Movable::moveTowards(float dist) {
		this->moveTowards(dist, this->rPos);
}

void Movable::moveTowards(float dist, float dir) {
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		this->xTarget += dist * cos(dir * DEG_TO_RAD);
		this->yTarget += dist * sin(dir * DEG_TO_RAD);
	}
}

float Movable::getX() {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
			return xPos;
	}
}

float Movable::getY() {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		return yPos;
	}
}

float Movable::getR() {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		return rPos;
	}
}
