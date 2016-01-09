/*
 * LCD.cpp
 *
 *  Created on: 02.10.2015
 *      Author: xasin
 */

#define NOP asm volatile ("nop")

#define RS 0
#define RW 1
#define EN 2
#define DATA 3

#include "LCD.h"


#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

	//Mark the according bit for the character n so that it will be updated
	void LCD::mark(uint8_t n, uint8_t y) {
		if(n < 32) {
			if(y == 0)	//Should the bit be set or unset?
				dispUpdate[n/8] &= ~(1<< n%8);
			else
				dispUpdate[n/8] |= (1<< n%8);
		}
	}

	//Scan for the next marked bit that shall be updated
	uint8_t LCD::nextMark() {
		for(uint8_t i=0; i < 4; i++) {
			if(dispUpdate[i] != 0) {	//Only check that part of the array if there actually is something in there.
				for(uint8_t j=0; j < 8; j++) {
					if((dispUpdate[i] & (1<<j)) != 0) {
						return i*8 + j;
					}
				}
			}
		}
		return 255;		//If nothing was found, return 255.
	}

	//Read out if the LCD is busy. True for yes, false for not busy.
	uint8_t LCD::readBusy() {
		uint8_t temp = 0;
		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			*(PORT -1) &= ~(0b1111 << DATA); 			//Set the data pins as inputs (for reading in the data.)

			*PORT |= (1<< RW);						//Enable read mode
			NOP;
			*PORT |= (1<< EN);						//Enable
			NOP;
			temp = (*(PORT -2) & (0b1000<< DATA));		//Read out the busy flag bit.
			*PORT &= ~(1<<EN);

			NOP;

			*PORT |= (1<<EN);						//Second enable (4 bit operation)
			NOP;
			*PORT &= ~(1<<EN | 1<< RW);

			*(PORT -1) |= (0b1111 << DATA); 				//Set the pins back to output.
		}
		if(temp == 0)
			return false;
		else
			return true;
	}

	//Wait while the LCD display is busy.
	void LCD::waitWhileBusy() {
		while(readBusy() == true) {
		}
	}

	//Push data, either a character or a command, to the LCD.
	void LCD::pushData(uint8_t msg, uint8_t controlBit) {
		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			//Write the first 4 bits of data to the display, the control bit, and enable.
			NOP;
			*PORT |= ((msg & 0b11110000)>>4 <<DATA | controlBit<<RS | 1<< EN);
			NOP;
			*PORT &= ~(1<< EN | 0b1111<< DATA);

			//Do the same with the last 4 bits.
			NOP;
			*PORT |= (1<< EN | (msg & 0b00001111) << DATA);
			NOP;
			*PORT &= ~(1<< EN | 0b1111<< DATA | 1<< RS);	//Reset the outputs.
		}
	}

	//place the cursor at the specified position. This is differnt from setCursor, as it directly sends the value to the LCD.
	void LCD::placeCursor(uint8_t n) {
		if(n != currentCursor) {	//Only proceed if the current cursor isn't already there.
			currentCursor = n;
			if(n >= 16) {
				n += LCD_LINE_2 - 16;	//If n is above 15, it means that it is on the second line and not the first.
			}
			pushData(SETDDRAM(n),0);
		}
	}

	LCD::LCD(volatile uint8_t *P) {
		PORT = P;					//Define the pointer for the display port.
		currentCursor = 0;
		cursor = 0;

		*(PORT -1) |= (0b01111111);		//Set all those pins to outputs.

		*PORT |= (0b0011<< DATA | 1<< EN);	//Enable 8-Bit mode! (For reset)
		NOP;
		*PORT &= ~(1<< EN | 0b0001<< DATA);	//Reset the inputs again.
		NOP;

		*PORT |= (1<< EN);
		NOP;
		*PORT &= ~(1<< EN | 0b0001<< DATA);

		//General Display Setup
		waitWhileBusy();
		pushData(SETUP(0,1,0),0);		//4-Bit mode, 2 Lines, 5x8
		waitWhileBusy();
		pushData(DISPMODE(1,0,0),0);	//Enable Display, currentCursor and Blink
		waitWhileBusy();
		pushData(CLEARDISP,0);			//Set the currentCursor back to home pos.
	}

	//Update the display /one at a time/.
	//This is suitable for ISR Routine updating without taking too long. Very efficient.
	void LCD::update() {
		if(readBusy() == false) {				//Only continue if the display is ready for instructions.
			uint8_t nMark = nextMark();			//Read out if there is a character to be upadted, and which one.
			if(nMark != 255) {
				if(nMark != currentCursor) {	//Only set the currentCursor if it isn't in the correct position already.
					placeCursor(nMark);
				}
				else {
					pushData(dispData[nMark],1);	//Push the data, unmark the bit and push the currentCursor one forwards
					mark(nMark,0);
					currentCursor++;
				}
			}
			else {
				placeCursor(cursor);
			}
		}
	}

	//write out a String to the display, starting at "start" and going until the end signal was found.
	void LCD::writeString(const char* input, uint8_t start) {
		for(uint8_t i=start; i<32; i++) {
			if(input[i - start] == '\0')			//Break out of the loop at the end signal.
				break;
			else {
				ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
					dispData[i] = input[i - start];	//Write the according string char to the display buffer and mark.
					mark(i,1);
				}
			}
		}

	}

	//Write out a number onto the screen, starting at "start" and displaying "len" characters (in base 10)
	void LCD::writeNum(uint16_t n, uint8_t start, uint8_t len) {
		uint32_t x=1;
		uint32_t oN=0;
		for(uint8_t i=1; i < len; i++) {
			x *= 10;
		}
		for(int8_t i=0; i < len; i++) {
			if(start+i < 32) {
				ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
					dispData[start + i] = (n/ x) - oN + 48;
					mark(start + i, 1);
				}
				oN = (n/x)*10;
				x /= 10;
			}
			else
				break;
		}
	}


	//Set the currentCursor to position "n"
	void LCD::setCursor(uint8_t n) {
		if(n < 32) {
			cursor = n;
		}
	}

	//Enable or disable currentCursor blink, or currentCursor at all. (0 = off, 1 = currentCursor, 2 = currentCursor + blink)
	void LCD::cursorMode(uint8_t m) {
		if(m < 3) {
			waitWhileBusy();
			uint8_t msg = 0;
			switch(m) {
			case 0:
				msg = DISPMODE(1,0,0);
			break;
			case 1:
				msg = DISPMODE(1,1,0);
			break;
			case 2:
				msg = DISPMODE(1,1,1);
			break;
			}

			pushData(msg,0);
		}
	}
