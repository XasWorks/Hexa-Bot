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

uint8_t abs(int8_t i) {
	if(i > 0)
		return i;
	else
		return -i;
}

int main() {

	System.Motor.setAcceleration(100);
	System.Motor.setSpeed(100);
	System.Motor.setRotationSpeed(100);

	while(true) {
		if(System.Motor.atPosition() && LFSensor.lineStatus == LF_OK)
			System.Motor.moveTowards(50);


		if(System.Motor.atRotation()) {
			if(LFSensor.lineStatus == LF_OK && LFSensor.lineOffset != 0) {
				System.Motor.setRotationSpeed((abs(LFSensor.lineOffset) * 100) / LF_RIGHT);
			}
			else if(LFSensor.lineStatus == LF_LOST) {
				System.Motor.setRotationSpeed(200);
			}

			if(LFSensor.lineOffset > 0)
				System.Motor.rotateBy(-1);
			if(LFSensor.lineOffset < 0)
				System.Motor.rotateBy(1);
		}

	}

	return 0;
}
