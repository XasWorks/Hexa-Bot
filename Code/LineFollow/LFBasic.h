/*
 * LFBasic.h
 *
 *  Created on: Jan 3, 2016
 *      Author: xasin
 */

#ifndef CODE_LINEFOLLOW_LFBASIC_H_
#define CODE_LINEFOLLOW_LFBASIC_H_

#include <avr/io.h>
#include "../Updatable.h"

class LFBasic : Updatable {
public:
	uint8_t lineStatus = 0;
	int8_t 	lineOffset = 0;

	LFBasic();
};

#endif /* CODE_LINEFOLLOW_LFBASIC_H_ */
