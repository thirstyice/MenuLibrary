#pragma once

#include "MenuOutput.h"
#include <LiquidCrystal_PCF8574.h>



class MenuOutputPCF8574 : public MenuOutput {
public:
	MenuOutputPCF8574(LiquidCrystal_PCF8574* _lcd, uint8_t _width, uint8_t _height) : 
		lcd(_lcd) {width = _width; height = _height;}
	void setCursor(unsigned char newCursor) {textCursor = newCursor;};
	void drawLine(uint8_t line, String contents);
	void setFocusedLine(uint8_t line);

private:
	unsigned char textCursor = 126;
	LiquidCrystal_PCF8574* lcd;
};
