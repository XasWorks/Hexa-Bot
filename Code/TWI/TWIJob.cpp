/*
 * TWIJob.cpp
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#include "TWIJob.h"

TWI_M_Job *TWI_M_Job::nodeEnd = 0;

TWI_M_Job::TWI_M_Job() {
	this->nextNode = TWI_M_Job::nodeEnd;
	TWI_M_Job::nodeEnd = this;
}

void TWI_M_Job::beginOperation() {}
void TWI_M_Job::endOperation() {
	if(this->jobStatus != 0) {
		this->jobStatus--;
	}
}

void TWI_M_Job::error() {}

TWI_M_Job * TWI_M_Job::getHeadNode() {
	return TWI_M_Job::nodeEnd;
}
TWI_M_Job * TWI_M_Job::getNextNode() {
	return this->nextNode;
}

uint8_t TWI_M_Job::getStatus() {
	return this->jobStatus;
}
