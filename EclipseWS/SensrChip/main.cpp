/* main.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Code/TWI/TWIHandler.h"
#include "Code/ADC/ADC_Lib.h"

#include "Code/TIMER/Timer1.h"

#include "ServController.h"
#include "IRDistSensor.h"

ServController sController = ServController();
IRDistSensor IRSensor = IRDistSensor();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}

ISR(TIMER1_COMPA_vect) {
	IRSensor.update();
}

int main() {

	TWI_Handler::IO.setAddress(0b1111);

	DDRD |= (1 << 7);

	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_prescaler(TIMER1_PRESC_8);
	Timer1::set_OCR1A(F_CPU / 8 / 50);

	while(true) {
	}

	return 0;
}
