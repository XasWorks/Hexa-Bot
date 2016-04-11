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

#include "ServController.h"
#include "IRDistSensor.h"

ServController sController = ServController();
IRDistSensor IRSensor = IRDistSensor();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}


int main() {

	TWI_Handler::IO.setAddress(0b1111);

	DDRD |= (1 << 7);

	while(true) {
	}

	return 0;
}
