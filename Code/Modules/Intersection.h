/*
 * Intersection.h
 *
 *  Created on: Feb 3, 2016
 *      Author: xasin
 */

#ifndef CODE_MODULES_INTERSECTION_H_
#define CODE_MODULES_INTERSECTION_H_

#include "ModuleBasic.h"
#include "../System/Robot.h"
#include "../LineFollow/LFBasic.h"

#define FWD_CHECK_DIST 20
#define INTSEC_DIST 85

#define DEFAULT_DIR 0

namespace Module {

	class Intersection : public Basic{
	private:
		Robot *sys;
		LFBasic *sens;

		uint8_t iCount = 0;
		const uint8_t iCLen = 1;
		const int8_t iDir[3] = {0, 110, 110};

		void moveFWD();

	public:
		Intersection(Robot *system, LFBasic *sensor);


		void execute();
	};

} /* namespace Module */

#endif /* CODE_MODULES_INTERSECTION_H_ */
