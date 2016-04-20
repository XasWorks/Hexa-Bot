/*
 * BallFineGrab.h
 *
 *  Created on: Apr 20, 2016
 *      Author: xasin
 */

#ifndef MODULE_BALLFINEGRAB_H_
#define MODULE_BALLFINEGRAB_H_

#include "../Code/Modules/ModuleBasic.h"

#include "../Code/Movement/Locomotor.h"
#include "../Code/Movement/Subspace.h"

#include "../Code/System/Robot.h"

#include "../IRDistanceSensor.h"

class BallFineGrab : Module::Basic {
private:
	Robot *system;
	IRDistanceSensor *sensor;

	uint8_t getIRDist();

public:
	BallFineGrab(Robot *system, IRDistanceSensor *sensor);

	void execute();
};

#endif /* MODULE_BALLFINEGRAB_H_ */
