#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/System/Robot.h"
#include "Code/LineFollow/LF3Sens.h"
#include "Code/Modules/LFFollow.h"

Robot System = Robot();
LF3Sens LFSensor = LF3Sens();

using Module::LFFollow;
LFFollow LFSys = LFFollow(&System, &LFSensor);


ISR(TIMER1_COMPA_vect) {
	System.update();

	LFSensor.update();
}

int main() {

	System.Motor.setAcceleration(100);
	System.Motor.setSpeed(100);
	System.Motor.setRotationSpeed(100);

	while(true) {
		LFSys.execute();
	}

	return 0;
}
