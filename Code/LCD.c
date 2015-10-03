/*
 * LCD.c
 *
 *  Created on: 15.05.2015
 *      Author: xasin
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

uint8_t dispStep=0;
uint8_t dispTask=0;
uint8_t dispData[33];
uint8_t aDispData[33];

uint8_t readBusy() {
	LCDPORT &= ~(15<<DATA | 1<<RS);
	DDRA  &= ~(15<<(DATA));
	LCDPORT |= (1<<RW);

	LCDPORT |= (1<<EN);
	_delay_us(1);
	uint8_t temp = (PINA & (1<<(DATA+3)));
	LCDPORT &= ~(1<<EN);

	ENABLE;

	DDRA |= (15<<DATA);
	LCDPORT &= ~(1<<RW);
	return temp;
}

void pushData (uint8_t LCDByte, uint8_t control) {
	LCDPORT &= ~(1<<RW);
	if(control == 0) {
		LCDPORT &= ~(1<<RS);
	}
	else {
		LCDPORT |= (1<<RS);
	}

	uint8_t nibble = (LCDByte >> 4) & 15;
	LCDPORT &= ~(15<<DATA);
	LCDPORT |= (nibble<<DATA);
	ENABLE;

	nibble = (LCDByte) & 15;
	LCDPORT &= ~(15<<DATA);
	LCDPORT |= (nibble<<DATA);
	ENABLE;
}

void initDisplay() {
	LCDDDR |= (1<<RS | 1<<RW | 1<<EN |  15<<DATA);

	_delay_ms(1000);

	LCDPORT &= ~(15<<DATA);
	LCDPORT |= (3<<DATA);
	ENABLE;
	_delay_us(200);
	ENABLE;
	_delay_us(200);
	ENABLE;
	_delay_us(200);

	LCDPORT &= ~(15<<DATA);
	LCDPORT |= (0b0010 << DATA);
	ENABLE;

	while(readBusy() != 0) {}
	pushData(SETUP(0,1,0),0);
	while(readBusy() != 0) {}
	pushData(DISPMODE(1,0,0),0);
	while(readBusy() != 0) {}
	pushData(CLEARDISP,0);
}

void LCDClear() {
	for(uint8_t i=0; i<32; i++) {
		dispData[i] =' ';
	}
}

void LCDPrintString(char* message, uint8_t start) {
	for(uint8_t i=0; i<(32-start); i++) {
		if(message[i] == '\0') {
			break;
		}
		dispData[i+start] = message[i];
	}
}

uint16_t pTen(uint8_t i) {
	switch(i) {
	case 0:
		return 0;
	break;

	case 1:
		return 1;
	break;

	case 2:
		return 10;
	break;

	case 3:
		return 100;
	break;

	case 4:
		return 1000;
	break;

	case 5:
		return 10000;
	break;
	}
}

void LCDPrintNum(uint16_t nu, uint8_t start, uint8_t length) {
	uint16_t n = nu;
	for(uint8_t i=1; i <= length; i++) {
		if((start + (length-i)) < 32) {
			dispData[start + (length-i)] = (48 + (n/pTen(i)) - (n/(pTen(i)*10))*10);
		}
	}
}

void LCDSetChar(uint8_t c, uint8_t p) {
	if(p < 32) {
		dispData[p] = c;
	}
}

void LCDStep() {
	switch(dispStep) {
	case 0:
		for(uint8_t i=0; i<32; i++) {
			if(dispData[i] != aDispData[i]) {
				aDispData[i] = dispData[i];
				dispTask = i;
				dispStep++;
				break;
			}
		}
	break;

	case 1:
		if(readBusy() == 0) {
			if(dispTask < 16) {
				pushData (SETDDRAM(LCD_LINE1 + dispTask),0);
			}
			else if (dispTask < 32){
				pushData (SETDDRAM(LCD_LINE2 + (dispTask-16)),0);
			}

			dispStep++;
		}
	break;

	case 2:
		if(readBusy() == 0) {
			if(dispTask < 32) {
				pushData (aDispData[dispTask],1);
			}

			dispStep++;
		}
	break;

	case 3:
		if(readBusy() == 0) {
			uint8_t curPos = aDispData[32] & 0b00011111;

			if(curPos < 16) {
				pushData (SETDDRAM(LCD_LINE1 + curPos),0);
			}
			else if (dispTask < 32){
				pushData (SETDDRAM(LCD_LINE2 + (curPos-16)),0);
			}

			dispStep=0;
		}
	break;
	}

}
