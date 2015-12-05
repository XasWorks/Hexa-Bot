/*
 * main.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Code/I2C/I2CHandler.h"

I2CHandler test(1, 0);

ISR(TWI_vect) {
	test.update();
}

int main() {
	sei();

	uint8_t jibber[3] = {0,0,0};

	test.transmit(jibber,3);
}
