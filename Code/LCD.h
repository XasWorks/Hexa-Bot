/*
 * LCD.h
 *
 *  Created on: 15.05.2015
 *      Author: xasin
 */

#define RS 0
#define RW 1
#define EN 2
#define DATA 3
#define LCDPORT PORTA
#define LCDDDR  DDRA

#ifndef DATA
	#error "LCD Data pin start must be specified!"
#endif
#ifndef RS
	#error "LCD RS pin must be specified!"
#endif
#ifndef	RW
	#error "LCD Read/Write pin start must be specified!"
#endif
#ifndef EN
	#error "LCD Enable pin start must be specified!"
#endif
#ifndef LCDPORT
	#error "LCD PORT Must be specified!"
#endif

#ifndef LCD_H_
#define LCD_H_

#define ENABLE LCDPORT |= (1<<EN); _delay_us(1); PORTA &= ~(1<<EN)

#define CLEARDISP 	0b00000001
#define CURSHOME	0b00000010
#define CURSSHIFT(cURSSHIFTDIR, dISPFLUID) (0b00000100 | cURSSHIFTDIR<<1 | dISPFLUID)  			//0=Decrement, 1=Increment || 0=Solid, 1=Fluid
#define DISPMODE(dISPON, cURSON, cURSBLINK) (0b00001000 | dISPON<<2 | cURSON<<1 | cURSBLINK)
#define SHIFTMODE(dISPSHIFT, sHIFTDIR) (0b00010000 | cURSSHIFT<<3 | sHIFTDIR<<2)
#define SETUP(bITMODE, lINES, fONTMODE) (0b00100000 | bITMODE<<4 | lINES<<3 | fONTMODE<<2)
#define LCD_LINE1 0b00000000
#define LCD_LINE2 0b01000000
#define SETDDRAM(aDDRESS) (0b10000000 | (aDDRESS))


void LCDStep();
void initDisplay();
void LCDClear();
void LCDSetChar(uint8_t c, uint8_t p);
void LCDPrintString(char* message, uint8_t start);
void LCDPrintNum(uint16_t n, uint8_t start, uint8_t length);

#endif /* LCD_H_ */
