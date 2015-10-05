#ifndef _LCD_H
#define _LCD_H

#define CURSOR_OFF 0
#define CURSOR_ON 1
#define CURSOR_ON_BLINK 2


class LCD {
public:
	LCD(volatile uint8_t *PORT, volatile uint8_t *DDRP, volatile uint8_t *PINP);
	void updateDisplay();
	void writeString(const char* input, uint8_t start);
	void writeNum(uint16_t n, uint8_t start, uint8_t length);
	void setCursor(uint8_t position);
	void cursorMode(uint8_t mode);
};

#endif
