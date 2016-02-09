/*
 * ObjectAvoid.cpp
 *
 *  Created on: 09.02.2016
 *      Author: xasin
 */

#include "ObjectAvoid.h"

namespace Module {

ObjectAvoid::ObjectAvoid(Robot *system) {
	this->sys = system;
}

void ObjectAvoid::execute() {
	float fDir = sys->Motor.getR();

	sys->Motor.setSpeed(100);
	sys->Motor.setRotationSpeed(90);

	sys->Motor.moveTowards(30, fDir + 180);
	sys->Motor.flush();

	for(uint8_t i = 0; i < SEG_NUM; i++) {
		sys->Motor.moveTowards(SEG_LEN, fDir);
		fDir += SEG_ANGLE;
	}
}

} /* namespace Module */
