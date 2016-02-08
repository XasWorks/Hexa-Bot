/*
 * I2CJob.h
 *
 *  Created on: Dec 14, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_I2CJOB_H_

#include "Buffer.h"

class I2CJob {
public:
	I2CJob();

	virtual void I2CLoad();
	virtual void I2CFinish();
};

#define CODE_I2C_I2CJOB_H_
#endif /* CODE_I2C_I2CJOB_H_ */
