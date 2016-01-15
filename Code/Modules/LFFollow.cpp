/*
 * LFRotation.cpp
 *
 *  Created on: Jan 15, 2016
 *      Author: xasin
 */

#include "LFFollow.h"

namespace Module {

	LFFollow::LFFollow(Robot *system, LFBasic *sensor) {
		this->sys = system;
		this->sens = sensor;
	}

	void LFFollow::execute() {

		if(sys->Motor.atPosition() && sens->lineStatus == LF_OK)
			sys->Motor.moveTowards(75);


		if(sys->Motor.atRotation()) {
			if(sens->lineStatus == LF_OK && sens->lineOffset != 0) {
				sys->Motor.setRotationSpeed((((sens->lineOffset > 0) ? sens->lineOffset : -sens->lineOffset ) * 100) / LF_RIGHT);
			}
			else if(sens->lineStatus == LF_LOST) {
				sys->Motor.setRotationSpeed(200);
			}

			if(sens->lineOffset > 0)
				sys->Motor.rotateBy(-1);
			if(sens->lineOffset < 0)
				sys->Motor.rotateBy(1);
		}
	}

} /* namespace Module */
