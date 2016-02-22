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

	void Intersection::moveFWD() {
		while(this->sens->lineStatus == LF_INTSEC) {
			this->sys->Motor.moveTowards(1);
			this->sys->Motor.flush();
		}
	}

	void Intersection::execute() {
		this->sys->Motor.setSpeed(150);
		this->sys->Motor.setRotationSpeed(90);

		uint8_t init_dir = this->sens->lineOffset;

		// Move forwards until the intersection ends!
		this->moveFWD();

		// Break out of the function if there still is a normal line!
		if(this->sens->lineStatus == LF_OK)
			return;
		else
			this->sys->Motor.rotateBy( (init_dir > 0) ? -90 : 90);
			this->sys->Motor.flush();
	}

} /* namespace Module */
