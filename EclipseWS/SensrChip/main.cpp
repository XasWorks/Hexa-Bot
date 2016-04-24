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
#include "BrightSensor.h"

ServController sController = ServController();
IRDistSensor IRSensor = IRDistSensor();
BrightSensor BRSensor = BrightSensor();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}

ISR(ADC_vect) {
	ADC_Lib::update();

	IRSensor.adc_update();
	BRSensor.adc_update();
}

ISR(TIMER1_COMPA_vect) {
	IRSensor.update();
	BRSensor.update();
}

int main() {

	TWI_Handler::IO.setAddress(0b1111);
	ADC_Lib::init(ADC_PRSC_64);

	DDRD |= (1 << 0);

	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_prescaler(TIMER1_PRESC_8);
	Timer1::set_OCR1A(F_CPU / 8 / 50);

	sei();

	while(true) {
	}

	return 0;
}
