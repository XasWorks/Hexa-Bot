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

	void LFFollow::move() {
		if(sys->Motor.atPosition() && sens->lineStatus != LF_AMBIG)
			sys->Motor.moveTowards(35);
	}

	void LFFollow::setSpeeds() {
		if(sys->Motor.atRotation()) {
			if(sens->lineStatus == LF_OK) {
				if(sens->lineOffset != 0)
					sys->Motor.setRotationSpeed((sens->lineOffset * ROTATION_MAX_SPEED) / LF_RIGHT);
				sys->Motor.setSpeed(MOVEMENT_SPEED);
			}
			else if(sens->lineStatus == LF_LOST) {
				sys->Motor.setRotationSpeed(ROTATION_LOST_SPEED);
				if(sens->lineOffset != 0)
					sys->Motor.setSpeed(MOVEMENT_LOST_SPEED);
			}
		}
	}

	void LFFollow::rotate() {
		if(sys->Motor.atRotation()) {
			if(sens->lineOffset > 0)
				sys->Motor.rotateBy(-2);
			if(sens->lineOffset < 0)
				sys->Motor.rotateBy(2);
		}
	}

	void LFFollow::execute() {

		this->setSpeeds();

		this->rotate();
		this->move();
	}

}
