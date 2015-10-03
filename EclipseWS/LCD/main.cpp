/*
 * main.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: xasin
 */

#include "/home/xasin/RoboNet/Code/LCD.cpp"

int main() {

	LCD disp (&PORTA);
	disp.cursorMode(CURSOR_ON_BLINK);
	disp.writeString("Test!",0);
	disp.setCursor(16);

	for(uint8_t i=0; i<32; i++) {
		disp.updateDisplay();
	}
	return 0;
}
