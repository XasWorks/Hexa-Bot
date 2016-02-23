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
			this->sys->Motor.moveTowards(2);
			this->sys->Motor.flush();
		}

		this->sys->Motor.moveTowards(10);
		this->sys->Motor.flush();
	}

	void Intersection::execute() {
		this->sys->Motor.setSpeed(200);
		this->sys->Motor.setRotationSpeed(80);

		uint8_t init_dir = this->sens->lineOffset;

		// Move forwards until the intersection ends!
		// this->moveFWD();

		this->sys->Motor.rotateBy(100);
			this->sys->Motor.flush();
	}

} /* namespace Module */
