/*
 * Intersection.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: xasin
 */

#include "Intersection.h"

namespace Module {

	Intersection::Intersection(Robot *system, LFBasic *sensor) {
		this->sys = system;
		this->sens = sensor;
	}

	void Intersection::execute() {
		this->sys->Motor.setSpeed(50);
		this->sys->Motor.setRotationSpeed(90);

		this->sys->Motor.moveTowards(INTSEC_DIST);
		this->sys->Motor.rotateBy((sens->lineOffset > 0) ? 90 : -90);

		this->sys->Motor.flush();
	}

} /* namespace Module */
