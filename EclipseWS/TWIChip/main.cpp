/*
 * main.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: xasin
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "Code/TWI/TWIHandler.h"
#include "Code/TWI/TWIJob.h"

class IOExp : TWI_Job {
private:
	void setOutputs() {
		TWI_Handler::IO.buf.queue(0b01001110);
		TWI_Handler::IO.buf.queue(0x00);
		TWI_Handler::IO.buf.queue(0x00);
	}

	void enableLED() {
		TWI_Handler::IO.buf.queue(0b01001110);
		TWI_Handler::IO.buf.queue(0x14);
		TWI_Handler::IO.buf.queue(0b1);
	}

	void disableLED() {
		TWI_Handler::IO.buf.queue(0b01001110);
		TWI_Handler::IO.buf.queue(0x14);
		TWI_Handler::IO.buf.queue(0);
	}
public:

	void ledON() {
		this->jobStatus = 1;
		TWI_Handler::IO.searchJobs();
	}

	void ledOff() {
		this->jobStatus = 2;
		TWI_Handler::IO.searchJobs();
	}

	void beginOperation() {
		switch(this->jobStatus) {
		case 100:
			setOutputs();
			jobStatus = 0;
		break;

		case 2:
			disableLED();
		break;

		case 1:
			enableLED();
		break;
		}
	}

	void endOperation() {
		this->jobStatus = 0;
	}
	IOExp() {
		this->jobStatus = 100;
	}
};

IOExp ioJob = IOExp();

ISR(TWI_vect) {
	TWI_Handler::IO.update();
}

int main() {
	DDRD |= 1;

	_delay_ms(1000);

	TWI_Handler::IO.searchJobs();

	while(true) {
		ioJob.ledON();
		_delay_ms(1000);
		ioJob.ledOff();
		_delay_ms(1000);

	}
	return 0;
}
