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
	if(this->currentJob != 0) {
		this->currentJob = jobPointer;
		this->currentJob->beginOperation();

		this->start();
		this->clearTWINT();
	}
}
void TWI_Handler::endJob() {
	// Let the TWI_Job end it's operation
	this->currentJob->endOperation();

	// Check if the current job still wants to keep talking
	if(this->currentJob->getStatus() != 0) {
		this->start(); 			// Send a RepStart
	}
	// Otherwise, check if there is another Job available!
	else {
		this->currentJob = 0;
		this->searchJobs();

		// If there is no job requiring a further send
		if(this->currentJob == 0)
			this->stop();
	}
}

void TWI_Handler::searchJobs() {
	if(this->currentJob == 0) {
		// Initialise the node chain
		this->currentJob = TWI_Job::getHeadNode();

		// Go through the node chain until either a waiting job or the end of the chain is hit!
		while(this->currentJob != 0) {
			if(this->currentJob->getStatus() != 0)
				break;
			else
				this->currentJob = this->currentJob->getNextNode();
		}


		//If a new job was selected (old job == 0 and a new job present), excecute that one.
		this->beginJob(currentJob);
	}
}

void TWI_Handler::setSlaveJob(TWI_Job *slave) {
	this->slaveJob = slave;
}

void TWI_Handler::onMRFinish() {
	this->endJob();
}
void TWI_Handler::onMTFinish() {
	this->endJob();
}

void TWI_Handler::onSTStart() {
	this->slaveJob->beginOperation();
}
void TWI_Handler::onSRFinish() {
	this->slaveJob->beginOperation();
}
