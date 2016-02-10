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

	sys->Motor.setSpeed(100);
	sys->Motor.setRotationSpeed(90);

	sys->Motor.moveTowards(30, sys->Motor.getR() + 180);
	sys->Motor.flush();

	sys->Motor.moveTowards(100, sys->Motor.getR() + 90);
	sys->Motor.flush();
	sys->Motor.moveTowards(200);
	sys->Motor.flush();
	sys->Motor.moveTowards(100, sys->Motor.getR() - 90);
	sys->Motor.flush();

}

} /* namespace Module */
