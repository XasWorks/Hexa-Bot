/*
 * BallFineGrab.h
 *
 *  Created on: Apr 20, 2016
 *      Author: xasin
 */

#ifndef MODULE_BALLFINEGRAB_H_
#define MODULE_BALLFINEGRAB_H_

#include <util/delay.h>

#include "../Code/Modules/ModuleBasic.h"

#include "../Code/Movement/Locomotor.h"
#include "../Code/Movement/Subspace.h"

#include "../Code/System/Robot.h"

#include "../IRDistanceSensor.h"
#include "../ServoController.h"

#define GROUND_DISTANCE 200
#define BALL_CLOSE_DISTANCE 60

class BallFineGrab : Module::Basic {
private:
	Robot *system;
	IRDistanceSensor *sensor;
	ServoController  *servo;

	uint8_t getIRDist();

public:
	BallFineGrab(Robot *system, IRDistanceSensor *sensor, ServoController *servo);

	void execute();
};

#endif /* MODULE_BALLFINEGRAB_H_ */
