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
		this->sys->Motor.setSpeed(150);
		this->sys->Motor.setRotationSpeed(90);

		uint8_t init_dir = this->sens->lineOffset;

		// Checking if there is a line infront of us!
		this->sys->Motor.moveTowards(FWD_CHECK_DIST);
		this->sys->Motor.flush();
		// If there /is/ a line
		if(this->sens->lineStatus == LF_OK)
			return;
		//Though then, if there is NO line.
		else if(this->sens->lineStatus == LF_INTSEC) {
			while(this->sens->lineStatus == LF_INTSEC) {
				this->sys->Motor.moveTowards(1);
				this->sys->Motor.flush();
			}
			return;
		}
		else {
			//Original intersection handling code! Yay ...
			this->sys->Motor.moveTowards(INTSEC_DIST - FWD_CHECK_DIST);
			this->sys->Motor.rotateBy( (init_dir > 0) ? -90 : 90);
			this->sys->Motor.flush();
		}
	}

} /* namespace Module */
