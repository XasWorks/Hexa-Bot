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

#define SEG_NUM 5
#define SEG_RAD 100
#define SEG_ANGLE 180 / SEG_NUM
#define SEG_LEN sin(SEG_ANGLE / 2) * SEG_RAD * 2

namespace Module {

class ObjectAvoid : public Basic{
private:
	Robot *sys;

public:
	ObjectAvoid(Robot *system);

	void execute();
};

}

#endif /* CODE_MODULES_OBJECTAVOID_H_ */
