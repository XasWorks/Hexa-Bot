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

	sys->Motor.setSpeed(180);
	sys->Motor.setRotationSpeed(100);

	float initDir = sys->Motor.getR();

	sys->Motor.moveTowards(60, initDir + 180);
	sys->Motor.flush();

	int8_t dirmod = (distance < 200) ? 1 : -1;
//	if(oCount == oLen)
//		dirmod = oDirs[oCount];
//	else
//		dirmod = oDirs[oCount++];

	sys->Motor.moveTowards(SIDEWAYS_MOV, initDir - 90*dirmod);
	sys->Motor.flush();
	sys->Motor.moveTowards(FORWARDS_MOV);
	sys->Motor.flush();

	sys->Motor.moveTowards(1.05 * SIDEWAYS_MOV, initDir + 90*dirmod);
	sys->Motor.flush();

	sys->Motor.rotateBy(-50);
	sys->Motor.flush();
}

} /* namespace Module */
