#ifndef _LCD_H
#define _LCD_H

#include <avr/io.h>
#include "../Updatable.h"

#define CURSOR_OFF 0
#define CURSOR_ON 1
#define CURSOR_ON_BLINK 2

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

class LCD : Updatable {

private:
	volatile uint8_t dispData[32] = {0};
	volatile uint8_t dispUpdate[4]= {0};
	volatile uint8_t currentCursor;
	volatile uint8_t cursor;

	volatile uint8_t *PORT;
	volatile uint8_t *PINP;
	volatile uint8_t *DDRP;

	void mark(uint8_t n, uint8_t y);
	uint8_t nextMark();
	uint8_t readBusy();
	void waitWhileBusy();
	void pushData(uint8_t msg, uint8_t rsBit);
	void placeCursor(uint8_t n);

public:
	LCD(volatile uint8_t *PORT);
	void update();
	void writeString(const char* input, uint8_t start);
	void writeNum(uint16_t n, uint8_t start, uint8_t length);
	void setCursor(uint8_t position);
	void cursorMode(uint8_t mode);
};

#endif
