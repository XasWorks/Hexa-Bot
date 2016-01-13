#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/System/Robot.h"
#include "Code/LineFollow/LF3Sens.h"

	TranslativeStepper stepA = TranslativeStepper(&PORTD, 0, F_ISR1/F_CAL, STEPPING, 35, -30, 75);
	TranslativeStepper stepB = TranslativeStepper(&PORTD, 2, F_ISR1/F_CAL, STEPPING, 35, 30, 75);
	TranslativeStepper stepC = TranslativeStepper(&PORTD, 4, F_ISR1/F_CAL, STEPPING, 35, 180, 75);

	//ISR Prescaler value
	volatile uint16_t ISR1presc = 0;

	Locomotor Motor = Locomotor(&stepA, &stepB, &stepC, F_CAL);

Robot System = Robot();
LF3Sens LFSensor = LF3Sens();

ISR(TIMER1_COMPA_vect) {
	//Update the stepper motor controllers
	stepA.update();
	stepB.update();
	stepC.update();

	//Software prescaler for slower ISR for calculation updating
	ISR1presc++;
	if(ISR1presc == F_ISR1 / F_CAL) {
		Motor.update();
		ISR1presc = 0;
	}

	LFSensor.update();
}


int main() {

	System.init();

	Motor.setAcceleration(100);
	Motor.setSpeed(100);
	Motor.setRotationSpeed(100);

	while(true) {
		if(Motor.atPosition())
			Motor.moveTowards(50);


		if(Motor.atRotation()) {
			if(LFSensor.lineStatus == LF_OK && LFSensor.lineOffset != 0) {
				Motor.setRotationSpeed(fabs(LFSensor.lineOffset) * 100 / LF_RIGHT);
			}
			else if(LFSensor.lineStatus == LF_LOST) {
				Motor.setRotationSpeed(200);
			}

			if(LFSensor.lineOffset > 0)
				Motor.rotateBy(-1);
			if(LFSensor.lineOffset < 0)
				Motor.rotateBy(1);
		}

	}

	return 0;
}
