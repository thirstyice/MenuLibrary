#pragma once

#include "MenuOutput.h"
#include <Olimex16x2.h>

class MenuOutputOlimex16x2 : public MenuOutput {
public:
	MenuOutputOlimex16x2(Olimex16x2* _lcd) : 
		lcd(_lcd) {width = 16; height = 2;}
	void setCursor(unsigned char newCursor) {textCursor = newCursor;};
	void drawLine(uint8_t line, String contents);
	void setFocusedLine(uint8_t line);

private:
	unsigned char textCursor = 126;
	Olimex16x2* lcd;
};