#pragma once

#include "GenericTextBased.h"
#include <LiquidCrystal_PCF8574.h>



class MenuOutputPCF8574 : public MenuOutputGenericTextBased  {
public:
	MenuOutputPCF8574(LiquidCrystal_PCF8574* _lcd, uint8_t _width, uint8_t _height) :
		MenuOutputGenericTextBased(_width-1, _height, 126, 126, 127), // Width less cursor
		lcd(_lcd)
	{}
	void setCursor(char newCursor) {cursor=newCursor;}
	void outputLine(uint8_t line, char* contents, TitleFlags flags);
	void setFocusedLine(uint8_t line);
private:
	LiquidCrystal_PCF8574* lcd;
};


void MenuOutputPCF8574::outputLine(uint8_t lineIndex, char* line, TitleFlags flags) {
	if (flags.selectionLength > 0) {
		if (flags.alignRightFrom < flags.selectionStart) {
			flags.selectionStart += (width - strlen(line));
		}
		line[flags.selectionStart] = cursor;
	}
	lcd->setCursor(0, lineIndex);
	lcd->print(line);
	for (uint8_t i=strlen(line); i<width; i++) {
		lcd->print(" ");
	}
	lcd->print(flags.isSubmenu?submenuArrow:' ');
}

void MenuOutputPCF8574::setFocusedLine(uint8_t line) {
	if (line==focusedLine) {
		return;
	}
	lcd->setCursor(0, focusedLine);
	lcd->print(' ');
	lcd->setCursor(0, line);
	lcd->print(cursor);
	focusedLine = line;
}