#pragma once

#include "MenuOutput.h"
#include <Olimex16x2.h>

class MenuOutputOlimex16x2 : public MenuOutput {
public:
	MenuOutputOlimex16x2(Olimex16x2* _lcd) : 
		lcd(_lcd) {width = 16; height = 2;}
	void setCursor(unsigned char newCursor) {textCursor = newCursor;};

private:
	void doOutput(uint8_t startIndex, uint8_t numLines);
	unsigned char textCursor = 126;
	Olimex16x2* lcd;
};