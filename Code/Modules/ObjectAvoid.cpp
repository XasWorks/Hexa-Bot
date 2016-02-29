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
	sys->Motor.setRotationSpeed(90);

	sys->Motor.moveTowards(30, sys->Motor.getR() + 180);
	sys->Motor.flush();

	sys->Motor.moveTowards(SIDEWAYS_MOV, sys->Motor.getR() + 90);
	sys->Motor.flush();
	sys->Motor.moveTowards(FORWARDS_MOV);
	sys->Motor.flush();

	sys->Motor.moveTowards( 1.03 * SIDEWAYS_MOV, sys->Motor.getR() - 90);
	sys->Motor.flush();

}

} /* namespace Module */
