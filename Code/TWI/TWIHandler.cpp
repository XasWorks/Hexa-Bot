/*
 * TWIHandler.cpp
 *
 *  Created on: 01.03.2016
 *      Author: xasin
 */

#include "TWIHandler.h"

TWI_Handler TWI_Handler::IO = TWI_Handler();

TWI_Handler::TWI_Handler() {
	TWI_Basic::TWISys = this;
}

void TWI_Handler::beginJob(TWI_Job *jobPointer) {
	if(this->currentMasterJob != 0) {
		this->currentMasterJob = jobPointer;
		this->currentMasterJob->beginOperation();

		this->start();
		this->clearTWINT();
	}
}

TWI_Job * TWI_Handler::searchJobs() {
		// Initialise the node chain
		TWI_Job *sJob = TWI_Job::getHeadNode();

		// Go through the node chain until either a waiting job or the end of the chain is hit!
		while(sJob != 0) {
			if(sJob->getStatus() != 0)
				return sJob;
			else
				sJob = sJob->getNextNode();
		}
		return 0;
}

void TWI_Handler::endMasterJob() {
	// Let the TWI_Job end it's operation
	this->currentMasterJob->endOperation();

	// Check if the current job still wants to keep talking
	if(this->currentMasterJob->getStatus() != 0) {
		this->start(); 			// Send a RepStart
	}
	// Otherwise, check if there is another Job available!
	else {
		if((this->currentMasterJob = this->searchJobs()) == 0) {
			// If there is no job requiring a further send
			this->stop();
		}
		else {
			this->currentMasterJob->beginOperation();
			this->start();
		}
	}
}

void TWI_Handler::setSlaveJob(TWI_Job *slave) {
	this->currentSlaveJob = slave;
}

void TWI_Handler::onMRFinish() {
	this->endMasterJob();
}
void TWI_Handler::onMTFinish() {
	this->endMasterJob();
}

void TWI_Handler::onSTStart() {
	this->currentSlaveJob->beginOperation();
}
void TWI_Handler::onSRFinish() {
	this->currentSlaveJob->beginOperation();
}

void TWI_Handler::onError() {
	this->buf.clear();
	TWCR = (1<< TWEN | 1<< TWIE | 1<< TWEA | 1<< TWSTO);
}
