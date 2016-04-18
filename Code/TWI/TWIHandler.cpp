/*
 * TWIHandler.cpp
 *
 *  Created on: 01.03.2016
 *      Author: xasin
 */

#include "TWIHandler.h"

TWI_Handler TWI_Handler::IO = TWI_Handler();

void TWI_Handler::beginJob(TWI_M_Job *jobPointer) {
	if(this->currentMasterJob != 0) {
		this->currentMasterJob = jobPointer;
		this->currentMasterJob->beginOperation();

		this->start();
		this->clearTWINT();
	}
}
void TWI_Handler::endMasterJob() {
	if(this->currentMasterJob != 0) {
		this->currentMasterJob->endOperation();

		// Check if the current job still wants to keep talking
		if(this->currentMasterJob->getStatus() != 0) {
			this->start(); 			// Send a RepStart
		}
		// Otherwise, check if there is another Job available!
		else {

			this->buf.clear();	// A new job is starting, clear the buffer just to be safe!

			if((this->currentMasterJob = this->searchMasterJobs()) == 0) {
				// If there is no job requiring a further send
				this->stop();
			}
			else {
				this->currentMasterJob->beginOperation();
				this->start();
			}
		}
	}
}

void TWI_Handler::onMRFinish() {
	this->endMasterJob();
}
void TWI_Handler::onMTFinish() {
	this->endMasterJob();
}

void TWI_Handler::onSTStart() {
	TWI_S_Job *transmittingSlaveJob = this->searchSlaveJobs();
	if(transmittingSlaveJob != 0)
		transmittingSlaveJob->beginTransmission();
}
void TWI_Handler::onSRFinish() {
	this->fireSlaveJobs();
	this->buf.clear();
}

void TWI_Handler::onError() {
	this->currentMasterJob = 0;
	this->buf.clear();

	TWCR = (1<< TWEN | 1<< TWIE | 1<< TWEA | 1<< TWSTO);
}

TWI_M_Job * TWI_Handler::searchMasterJobs() {
		// Initialise the node chain
		TWI_M_Job *sJob = TWI_M_Job::getHeadNode();

		// Go through the node chain until either a waiting job or the end of the chain is hit!
		while(sJob != 0) {
			if(sJob->getStatus() != 0)
				return sJob;
			else
				sJob = sJob->getNextNode();
		}
		return 0;
}
TWI_S_Job * TWI_Handler::searchSlaveJobs() {
	TWI_S_Job *node = TWI_S_Job::getHeadNode();

	while(node != 0) {
		if(node->getStatus() != 0)
			return node;
		else
			node = node->getNextNode();
	}
	return 0;
}
void TWI_Handler::fireSlaveJobs() {
	TWI_S_Job *node = TWI_S_Job::getHeadNode();

	while(node != 0) {
		node->endTransmission();
		node = node->getNextNode();
	}
}

TWI_Handler::TWI_Handler() {
	TWI_Basic::TWISys = this;
	TWAR = 0;
}

void TWI_Handler::updateJobs() {
	if(this->currentMasterJob == 0)
		if( (this->currentMasterJob = this->searchMasterJobs()) != 0) {
			this->currentMasterJob->beginOperation();

			this->start();
			this->clearTWINT();
		}
}

void TWI_Handler::setAddress(uint8_t address) {
	TWAR = address << 1;
}
