/*
 * Buffer.h
 *
 *  Created on: Nov 17, 2015
 *      Author: xasin
 */

#ifndef CODE_I2C_BUFFER_H_
#define CODE_I2C_BUFFER_H_

#include <avr/io.h>

//How many bytes should the buffer contain?
#define BUF_SIZE 16

class Buffer {
private:
	//Buffer arrays for the values, as well as a counter for how many items are stored
	volatile uint8_t input[BUF_SIZE];
	volatile uint8_t inStore = 0;

	//Moves all the items of the list forwards by one
	void shift();

public:
	Buffer();

	//Returns the amount of items currently stored
	uint8_t isAvailable();

	//Returns the next item and removes it
	uint8_t read();
	//Returns the next (or specified) item without removing it
	uint8_t peek();
	uint8_t peek(uint8_t n);

	//Puts a item at the end of the list
	bool queue(uint8_t c);

	//Cleans out the buffer, resetting it.
	void clear();
};

#endif /* CODE_I2C_BUFFER_H_ */
