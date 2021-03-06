/*
 * ObjectAvoid.h
 *
 *  Created on: 09.02.2016
 *      Author: xasin
 */

#ifndef CODE_MODULES_OBJECTAVOID_H_
#define CODE_MODULES_OBJECTAVOID_H_

#include "ModuleBasic.h"
#include "../System/Robot.h"

#define DEG_TO_RAD 0.017453293

#define SIDEWAYS_MOV 150
#define FORWARDS_MOV 570

namespace Module {

class ObjectAvoid : public Basic{
private:
	Robot *sys;

	uint8_t oCount = 0;
	const uint8_t oLen = 1;
	const int8_t oDirs[2] = {1, -1};

public:
	ObjectAvoid(Robot *system);

	uint8_t distance;

	void execute();
};

}

#endif /* CODE_MODULES_OBJECTAVOID_H_ */
