#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Code/System/Robot.h"

Robot sys = Robot();

ISR(TIMER1_COMPA_vect) {
	sys.update();
}


int main() {

	while(true) {

	}

	return 0;
}
