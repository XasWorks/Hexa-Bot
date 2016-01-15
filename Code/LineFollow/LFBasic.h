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

#define LF_OK 		0	//The line is under the sensors and tracked
#define LF_AMBIG 	1	//The line is currently in an ambiguous state, no clear decision can be made
#define LF_LOST 	2	//No sensors have the line and it could be lost
#define LF_INTSEC	3	//A intersection has been found!

#define LF_RIGHT 	127
#define LF_LEFT 	-127

class LFBasic : Updatable {
public:
	volatile uint8_t	lineStatus = 0;
	volatile int8_t 	lineOffset = 0;

	LFBasic();
};

#endif /* CODE_LINEFOLLOW_LFBASIC_H_ */
