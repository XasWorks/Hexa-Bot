#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/System/Robot.h"
#include "Code/LineFollow/LF3Sens.h"

Robot System = Robot();
LF3Sens LFSensor = LF3Sens();

ISR(TIMER1_COMPA_vect) {
	System.update();
	LFSensor.update();
}


int main() {

	System.Motor.setAcceleration(500);
	System.Motor.setSpeed(100);
	System.Motor.setRotationSpeed(100);

	while(true) {
		if(System.Motor.atPosition())
			System.Motor.moveTowards(50);


		if(System.Motor.atRotation()) {
			if(LFSensor.lineStatus == LF_OK) {
				System.Motor.setRotationSpeed(80);
				if(LFSensor.lineOffset > 0)
					System.Motor.rotateBy(-1);
				if(LFSensor.lineOffset < 0)
					System.Motor.rotateBy(1);
			}
			else if(LFSensor.lineStatus == LF_LOST) {
				System.Motor.setRotationSpeed(200);
				if(LFSensor.lineOffset > 0)
					System.Motor.rotateBy(-1);
				if(LFSensor.lineOffset < 0)
					System.Motor.rotateBy(1);
			}
		}

	}

	return 0;
}
