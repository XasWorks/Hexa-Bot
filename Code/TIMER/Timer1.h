/*
 * Timer1.h
 *
 *  Created on: 11.04.2016
 *      Author: xasin
 */

#ifndef CODE_TIMER_TIMER1_H_
#define CODE_TIMER_TIMER1_H_

#include <avr/io.h>

#define TIMER1_PRESC_OFF 	0b000
#define TIMER1_PRESC_1		0b001
#define TIMER1_PRESC_8		0b010
#define TIMER1_PRESC_64		0b011
#define TIMER1_PRESC_256	0b100
#define TIMER1_PRESC_1024	0b101

#define TIMER1_MODE_CTC 0

namespace Timer1 {
	void set_prescaler(uint8_t prescValue);
	void set_mode(uint8_t mode);
	void set_OCR1A(uint16_t value);
}

#endif /* CODE_TIMER_TIMER1_H_ */
