/*
 * LCD.cpp
 *
 *  Created on: 02.10.2015
 *      Author: xasin
 */

#define CURSOR_OFF 0
#define CURSOR_ON 1
#define CURSOR_ON_BLINK 2

#define NOP asm volatile ("nop")

#define RS 0
#define RW 1
#define EN 2
#define DATA 3

//LCD-Command to clear the display
#define CLEARDISP 	0b00000001
//LCD-Command to set the currentCursor home
#define CURSHOME	0b00000010
//LCD-Command to specify the move direction (1 = increment, 0 = decrement) and if the display should be shifted (1) or not (0).
#define CURSSHIFT(cURSSHIFTDIR, dISPFLUID) (0b00000100 | cURSSHIFTDIR<<1 | dISPFLUID)
//LCD-Command to turn display on/off, show the currentCursor and make it blink/static.
#define DISPMODE(dISPON, cURSON, cURSBLINK) (0b00001000 | dISPON<<2 | cURSON<<1 | cURSBLINK)
//LCD-Command to shift the display (1) or currentCursor (0) one right (1) or left (0).
#define SHIFTMODE(sHIFT, sHIFTDIR) (0b00010000 | sHIFT<<3 | sHIFTDIR<<2)
//LCD-Command to set up the display, specifying bitmode (1 == 8 bit, 0 == 4 bit), how many lines the display has (1 == 2 lines, 0 == 1) and if the characters are 5x10 (1) or 5x8 (0)
#define SETUP(bITMODE, lINES, fONTMODE) (0b00100000 | bITMODE<<4 | lINES<<3 | fONTMODE<<2)
//Data address for the first Line.
#define LCD_LINE_1 0b00000000
//Data address for the second Line.
#define LCD_LINE_2 0b01000000
//Command to set the LCD Memory address (character).
#define SETDDRAM(aDDRESS) (0b10000000 | (aDDRESS))


#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

class LCD {
private:
	volatile uint8_t dispData[32] = {0};
	volatile uint8_t dispUpdate[4]= {0};
	volatile uint8_t currentCursor;
	volatile uint8_t cursor;

	volatile uint8_t *PORT;
	volatile uint8_t *PINP;
	volatile uint8_t *DDRP;

	//Mark the according bit for the character n so that it will be updated
	void mark(uint8_t n, uint8_t y) {
		if(n < 32) {
			if(y == 0)
				dispUpdate[n/8] &= ~(1<< n%8);
			else
				dispUpdate[n/8] |= (1<< n%8);
		}
	}

	//Scan for the next marked bit that shall be updated
	uint8_t nextMark() {
		for(uint8_t i=0; i < 4; i++) {
			if(dispUpdate[i] != 0) {
				for(uint8_t j=0; j < 8; j++) {
					if((dispUpdate[i] & (1<<j)) != 0) {
						return i*8 + j;
					}
				}
			}
		}
		return 255;
	}

	//Return the length of a character array (String), ending with new line.
	uint8_t getStrLen(char* input) {
		for(uint8_t i=0; i < 32; i++) {
			if(input[i] == '\n')
				return i+1;
			else
				return 0;
		}
	}

	//Read out if the LCD is busy. True for yes, false for not busy.
	uint8_t readBusy() {
		uint8_t temp = 0;
		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			*DDRP &= ~(0b1111 << DATA); 			//Set the data pins as inputs (for reading in the data.)

			*PORT |= (1<< RW);						//Enable read mode
			NOP;
			*PORT |= (1<< EN);						//Enable
			NOP;
			temp = (*PINP & (0b1000<< DATA));		//Read out the busy flag bit.
			*PORT &= ~(1<<EN);

			NOP;

			*PORT |= (1<<EN);						//Second enable (4 bit operation)
			NOP;
			*PORT &= ~(1<<EN | 1<< RW);

			*DDRP |= (0b1111 << DATA); 				//Set the pins back to output.
		}
		if(temp == 0)
			return false;
		else
			return true;
	}

	//Wait while the LCD display is busy.
	void waitWhileBusy() {
		while(readBusy() == true) {
		}
	}

	//Push data, either a character or a command, to the LCD.
	void pushData(uint8_t msg, uint8_t controlBit) {
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

	void placeCursor(uint8_t n) {
		if(n != currentCursor) {
			currentCursor = n;
			if(n >= 16) {
				n += LCD_LINE_2 - 16;
			}
			pushData(SETDDRAM(n),0);
		}
	}

public:
	LCD(volatile uint8_t *P) {
		PORT = P;					//Define the pointer for the display port.
		DDRP = P -1;				//Get the Direction Register (port address -1)
		PINP = P -2;				//Get the Pin Register (port address -2)
		currentCursor = 0;
		cursor = 0;

		*DDRP |= (0b01111111);		//Set all those pins to outputs.

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
	void updateDisplay() {
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

	void writeString(const char* input, uint8_t start) {
		for(uint8_t i=start; i<32; i++) {
			if(input[i - start] == '\0')
				break;
			else {
				ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
					dispData[i] = input[i - start];
					mark(i,1);
				}
			}
		}

	}

	void writeNum(uint16_t n, uint8_t start, uint8_t len) {
		uint16_t x=1;
		uint16_t oN=0;
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
	void setCursor(uint8_t n) {
		if(n < 32) {
			cursor = n;
		}
	}

	//Enable or disable currentCursor blink, or currentCursor at all. (0 = off, 1 = currentCursor, 2 = currentCursor + blink)
	void cursorMode(uint8_t m) {
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
};
