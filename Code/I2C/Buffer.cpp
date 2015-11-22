/*
 * Buffer.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: xasin
 */

#include "Buffer.h"

void Buffer::shift() {
	for (uint8_t i=1; i < inStore; i++) {
		this->input[i -1] = this->input[i];
	}
	this->inStore--;
}

Buffer::Buffer() {
}

uint8_t Buffer::isAvailable() {
	return inStore;
}

uint8_t Buffer::read() {
	uint8_t temp = this->input[0];
	this->shift();
	return temp;
}

uint8_t Buffer::peek() {
	return this->input[0];
}

uint8_t Buffer::peek(uint8_t n) {
	if(n >= this->inStore)
		return 0;
	else
		return this->input[n];
}

bool Buffer::queue(uint8_t c) {
	if(this->inStore == BUF_SIZE)
		return false;
	else {
		this->input[this->inStore++] = c;
		return true;
	}
}

void Buffer::clean() {
	this->input[0] = 0;
	this->inStore = 0;
}
