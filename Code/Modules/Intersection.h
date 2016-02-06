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

#define INTSEC_DIST 75

namespace Module {

	class Intersection : public Basic{
	private:
		Robot *sys;

	public:
		Intersection(Robot *system);

		void execute();
	};

} /* namespace Module */

#endif /* CODE_MODULES_INTERSECTION_H_ */
