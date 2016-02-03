/*
 * LFRotation.h
 *
 *  Created on: Jan 15, 2016
 *      Author: xasin
 */

#ifndef CODE_MODULES_LFFOLLOW_H_
#define CODE_MODULES_LFFOLLOW_H_

#include "ModuleBasic.h"

#include "../System/Robot.h"
#include "../LineFollow/LFBasic.h"

#define ROTATION_MAX_SPEED 90
#define ROTATION_LOST_SPEED 150

#define MOVEMENT_SPEED 120
#define MOVEMENT_LOST_SPEED 10


namespace Module {

	class LFFollow : public Basic {
		Robot *sys;
		LFBasic *sens;

	private:
		void setSpeeds();
		void move();
		void rotate();



	public:
		LFFollow(Robot *system, LFBasic *sensor);

		void execute();
	};

}

#endif /* CODE_MODULES_LFFOLLOW_H_ */
