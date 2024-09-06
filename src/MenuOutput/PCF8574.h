#pragma once

#include "GenericTextBased.h"
#include <LiquidCrystal_PCF8574.h>



class MenuOutputPCF8574 : public MenuOutputGenericTextBased  {
public:
	MenuOutputPCF8574(LiquidCrystal_PCF8574* _lcd, uint8_t _width, uint8_t _height) :
		lcd(_lcd) {width = _width; height = _height;}
	void setCursor(char newCursor) {controlChars[MenuChars::StartOfSelection]=newCursor;}
	void outputLine(uint8_t line, String* contents);
	void setFocusedLine(uint8_t line);
private:
	char controlChars[MenuChars::Count] = {
		1,
		126,
		1,
		1,
		2,
		1,
		127,
		3
	};
	char getControlChar(uint8_t character) {if (character<=MenuChars::Count){return controlChars[character];}return -1;}
	LiquidCrystal_PCF8574* lcd;
};


void MenuOutputPCF8574::outputLine(uint8_t lineIndex, String* line) {
	bool isSubmenu = line->endsWith(String(controlChars[MenuChars::SubmenuArrow]));
	if (isSubmenu) {
		line->remove(line->length()-1);
	}
	int alignRightFrom = line->indexOf(controlChars[MenuChars::AlignRightFollowing]);
	line->remove(alignRightFrom, 1);
	lcd->setCursor(0, lineIndex);
	lcd->print((lineIndex==focusedLine)?controlChars[MenuChars::StartOfSelection]:' ');
	if (width > (line->length()+isSubmenu) && alignRightFrom != -1) {
		if (alignRightFrom > 0) {
			lcd->print(line->substring(0, alignRightFrom));
		}
		for (uint8_t i=line->length(); i<width; i++) {
			lcd->print(' ');
		}
		lcd->rightToLeft();
		lcd->setCursor(width-1, lineIndex);
		if (isSubmenu) {
			line += (char)126;
		}
		for (int8_t j=(line->length()-1); j>=alignRightFrom; j--) {
			lcd->print(line->charAt(j));
		}
		lcd->leftToRight();
	} else {
		lcd->print(line->substring(0,width-1));
		for (uint8_t i=line->length(); i<width-1; i++) {
			lcd->print(' ');
		}
		if (isSubmenu) {
			lcd->setCursor(width-1, lineIndex);
			lcd->write(126);
		}

	}
}

void MenuOutputPCF8574::setFocusedLine(uint8_t line) {
	if (line==focusedLine) {
		return;
	}
	lcd->setCursor(0, focusedLine);
	lcd->print(' ');
	lcd->setCursor(0, line);
	lcd->print(controlChars[MenuChars::StartOfSelection]);
	focusedLine = line;
}