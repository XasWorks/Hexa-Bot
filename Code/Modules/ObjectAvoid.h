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

public:
	ObjectAvoid(Robot *system);

	void execute();
};

}

#endif /* CODE_MODULES_OBJECTAVOID_H_ */
