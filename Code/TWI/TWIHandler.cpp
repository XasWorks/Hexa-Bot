/*
 * TWIHandler.cpp
 *
 *  Created on: 01.03.2016
 *      Author: xasin
 */

#include "TWIHandler.h"

TWI_Handler::TWI_Handler() {
	// TODO Auto-generated constructor stub

}

void TWI_Handler::beginJob(TWI_Job *jobPointer) {
	jobPointer->beginOperation();
	this->start();
	this->clearTWINT();
}

void TWI_Handler::onMRFinish() {
	this->endJob();
}
void TWI_Handler::onMTFinish() {
	this->endJob();
}
void TWI_Handler::endJob() {
	// Let the TWI_Job end it's operation
	this->curentJob->endOperation();

	// Check if the current job still wants to keep com'ing
	if(this->curentJob->getStatus() != 0) {
		this->start(); 			// Send a RepStart
	}
	// Otherwise, check if there is another Job available!
	else {
		this->curentJob = 0;
		this->searchJob();

		// If there IS another job requiring TWI, do a RepStart
		if(this->curentJob != 0) {
			this->curentJob->beginOperation();
			this->start();
		}
		// Otherwise, end transmission
		else
			this->stop();
	}
}
