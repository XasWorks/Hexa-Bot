/*
 * Intersection.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: xasin
 */

#include "Intersection.h"

namespace Module {

	Intersection::Intersection(Robot *system) {
		this->sys = system;
	}

	void Intersection::execute() {
		this->sys->Motor.setSpeed(100);
		this->sys->Motor.setRotationSpeed(90);

		this->sys->Motor.moveTowards(INTSEC_DIST);
		this->sys->Motor.rotateBy(90);

		this->sys->Motor.flush();
	}

} /* namespace Module */
