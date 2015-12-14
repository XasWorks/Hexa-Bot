/*
 * I2CJob.h
 *
 *  Created on: Dec 14, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CJOB_H_
#define CODE_I2C_I2CJOB_H_

#include "Buffer.h"

class I2CJob {
public:
	I2CJob();

	virtual void I2CInit(Buffer *output);
	virtual void I2CFinish(Buffer *input);
};

#endif /* CODE_I2C_I2CJOB_H_ */
