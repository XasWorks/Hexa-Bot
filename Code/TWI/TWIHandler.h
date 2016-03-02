/*
 * TWIHandler.h
 *
 *  Created on: 01.03.2016
 *      Author: xasin
 */

#ifndef CODE_TWI_TWIHANDLER_H_
#define CODE_TWI_TWIHANDLER_H_

#include "TWIBasic.h"
#include "TWIJob.h"
#include "TWI_StatCodes.h"

class TWI_Handler : TWI_Basic {

private:
	TWI_Job *currentJob = 0;

	// TWI Job to handle slave-line communication
	TWI_Job *slaveJob = 0;

	// Start a new job
	void beginJob(TWI_Job * jobPointer);
	// End a new job or send a repstart.
	void endJob();


public:
	TWI_Handler();

	void searchJobs();

	void setSlaveJob(TWI_Job *slave);

	void onMTFinish();
	void onMRFinish();

	void onSTStart();
	void onSRFinish();
};

#endif /* CODE_TWI_TWIHANDLER_H_ */
