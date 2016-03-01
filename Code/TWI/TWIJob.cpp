/*
 * TWIJob.cpp
 *
 *  Created on: 29.02.2016
 *      Author: xasin
 */

#include "TWIJob.h"

TWI_Job *TWI_Job::nodeEnd = 0;

TWI_Job::TWI_Job() {
	this->nextNode = TWI_Job::nodeEnd;
	TWI_Job::nodeEnd = this;
}

void TWI_Job::beginOperation() {}
void TWI_Job::endOperation() {}

void TWI_Job::error() {}

TWI_Job * TWI_Job::getHeadNode() {
	return TWI_Job::nodeEnd;
}

TWI_Job * TWI_Job::getNextNode() {
	return this->nextNode;
}
