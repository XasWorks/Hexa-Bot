/*
 * LF3Sens.h
 *
 *  Created on: Jan 3, 2016
 *      Author: xasin
 */

#ifndef CODE_LINEFOLLOW_LF3SENS_H_
#define CODE_LINEFOLLOW_LF3SENS_H_

#include <avr/io.h>
#include "LFBasic.h"

class LF3Sens : public LFBasic {
public:
	LF3Sens();

	void update();
};

#endif /* CODE_LINEFOLLOW_LF3SENS_H_ */
