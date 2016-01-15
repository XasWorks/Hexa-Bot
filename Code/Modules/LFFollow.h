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

namespace Module {

	class LFFollow : public Basic {
		Robot *sys;
		LFBasic *sens;

	public:
		LFFollow(Robot *system, LFBasic *sensor);

		void execute();
	};

}

#endif /* CODE_MODULES_LFFOLLOW_H_ */
