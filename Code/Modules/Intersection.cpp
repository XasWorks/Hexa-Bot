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

		// Checking if there is a line infront of us!
		this->sys->Motor.moveTowards(100);
		this->sys->Motor.flush();
		if(this->sens->lineStatus == LF_OK)
			return;

		//Returning to original position
		this->sys->Motor.moveTowards(-100);
		this->sys->Motor.flush();

		//Backing up ...
		uint16_t passedSteps = 0;
		while(this->sens->lineOffset != 0) {
			if(passedSteps ++ > 100)
				return;
			this->sys->Motor.moveTowards(-1);
			this->sys->Motor.flush();
		}
		this->sys->Motor.moveTowards(10);
		this->sys->Motor.flush();

		this->sys->Motor.moveTowards(INTSEC_DIST);

		this->sys->Motor.rotateBy( (this->sens->lineOffset > 0) ? -90 : 90);
	}

} /* namespace Module */
