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

class TWI_Handler : public TWI_Basic {
private:
	TWI_M_Job *currentMasterJob = 0;

	// Start a new job
	void beginJob(TWI_M_Job * jobPointer);
	// End a new job or send a repstart.
	void endMasterJob();

	// TWI_Basic overrider functions.
	void onMTFinish();
	void onMRFinish();

	void onSTStart();
	void onSRFinish();

	void onError();

	TWI_M_Job * searchMasterJobs();
	TWI_S_Job * searchSlaveJobs();
	void fireSlaveJobs();

public:
	static TWI_Handler IO;

	TWI_Handler();

	void updateJobs();

	void setAddress(uint8_t address);
};

#endif /* CODE_TWI_TWIHANDLER_H_ */
