#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "Code/System/Robot.h"
#include "Code/LineFollow/LF3Sens.h"

#include "Code/Modules/LFFollow.h"
#include "Code/Modules/Intersection.h"
#include "Code/Modules/ObjectAvoid.h"

Robot System = Robot();
LF3Sens LFSensor = LF3Sens();

using namespace Module;
LFFollow LFSys = LFFollow(&System, &LFSensor);
Intersection INTSECSys = Intersection(&System, &LFSensor);
ObjectAvoid AVDSys = ObjectAvoid(&System);

Basic *cModule;

ISR(TIMER1_COMPA_vect) {
	System.update();

	LFSensor.update();
}

#define TASK_LF 0
#define TASK_INTSEC 1

uint8_t currentTask = TASK_LF;

void setTask() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	switch(currentTask) {
		case TASK_LF:
			if(LFSensor.lineStatus == LF_INTSEC) {
				currentTask = TASK_INTSEC;
				cModule = &INTSECSys;
			}
		break;

		case TASK_INTSEC:
			currentTask = TASK_LF;
			cModule = &LFSys;
		break;
		}
	}
}

int main() {

	cModule = &LFSys;

//	while(true) {
//		setTask();
//
//		cModule->execute();
//	}

	System.Motor.setSpeed(50);

	while(true) {
		System.Motor.moveBy(100, 0);
		System.Motor.flush();

		System.Motor.moveBy(0, 100);
		System.Motor.flush();

		System.Motor.moveTo(0, 0);
		System.Motor.flush();
	}

	return 0;
}
