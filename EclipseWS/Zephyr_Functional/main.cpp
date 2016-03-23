#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "Code/System/Robot.h"
#include "Code/LineFollow/LF3Sens.h"

#include "Code/TWI/TWIHandler.h"
#include "Code/TWI/TWIJob.h"

#include "Code/Modules/LFFollow.h"
#include "Code/Modules/Intersection.h"
#include "Code/Modules/ObjectAvoid.h"

#include "ServoController.h"

Robot System = Robot();
LF3Sens LFSensor = LF3Sens();

using namespace Module;
LFFollow LFSys = LFFollow(&System, &LFSensor);
Intersection INTSECSys = Intersection(&System, &LFSensor);
ObjectAvoid AVDSys = ObjectAvoid(&System);

ServoController servo = ServoController();

Basic *cModule;

ISR(TWI_vect) {
	PORTC |= (1);
	TWI_Handler::IO.update();
}

ISR(TIMER1_COMPA_vect) {
	System.update();

	LFSensor.update();
}

#define TASK_LF 	0
#define TASK_INTSEC 1
#define TASK_OBJ 	2

uint8_t currentTask = TASK_LF;

void setTask() {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
	switch(currentTask) {
		// -- STANDARD LF --
		case TASK_LF:

			// Switch to object avoidance mode
			if((PINC & (1<< 3)) == 0) {
				currentTask = TASK_OBJ;
				cModule = &AVDSys;
			}

			// Else, switch to Intersection mode
			else if ((LFSensor.lineStatus == LF_INTSEC)) {
				currentTask = TASK_INTSEC;
				cModule = &INTSECSys;
			}


		break;

		// -- INTERSECTION HANDLING --
		case TASK_INTSEC:
			currentTask = TASK_LF;
			cModule = &LFSys;
		break;

		// -- OBJECT HANDLING --
		case TASK_OBJ:
			currentTask = TASK_LF;
			cModule = &LFSys;
		break;
		}
	}
}

int main() {

	// Init of the touch sensor
	DDRC |= (1<< 3);

	cModule = &LFSys;

	System.Motor.setRotationSpeed(50);

	DDRC &= ~(1 << 0);
	PORTC &= ~(1 << 0);

	while(true) {
		_delay_ms(1000);
		servo.setServo(255);
		_delay_ms(1000);
		servo.setServo(0);
	}

	while(true) {
		setTask();

		cModule->execute();
	}


	return 0;
}
