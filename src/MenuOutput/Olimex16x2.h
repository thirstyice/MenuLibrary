#pragma once

#include "GenericTextBased.h"
#include <Olimex16x2.h>

class MenuOutputOlimex16x2 : public MenuOutputGenericTextBased {
public:
	MenuOutputOlimex16x2(Olimex16x2* _lcd) :
		lcd(_lcd) {width = 16; height = 2;}
	void setCursor(char newCursor) {controlChars[MenuChars::StartOfSelection]=newCursor;};
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
	Olimex16x2* lcd;
};

void MenuOutputOlimex16x2::outputLine(uint8_t lineIndex, String* line) {
	bool isSubmenu = line->endsWith(String(controlChars[MenuChars::SubmenuArrow]));
	if (isSubmenu) {
		line->remove(line->length()-1);
	}
	*line = ((lineIndex==focusedLine)?String(controlChars[MenuChars::StartOfSelection]):" ") + *line;
	int alignRightFrom = line->indexOf(controlChars[MenuChars::AlignRightFollowing]);
	line->remove(alignRightFrom, 1);
	if (width > (line->length()+isSubmenu) && alignRightFrom != -1) {
		lcd->drawLine(lineIndex, line->substring(0, alignRightFrom));
		uint8_t position = width;
		if (isSubmenu) {
			line += (char)126;
		}
		for (uint8_t j=(line->length()-1); j>=alignRightFrom; j--) {
			position--;
			lcd->drawChar(line->charAt(j), lineIndex, position);
		}
	} else {
		lcd->drawLine(lineIndex, *line);
		if (isSubmenu) {
			lcd->drawChar((char)126, lineIndex, width-1);
		}
	}
}

void MenuOutputOlimex16x2::setFocusedLine(uint8_t line) {
	if (line==focusedLine) {
		return;
	}
	lcd->drawChar(' ', focusedLine, 0);
	lcd->drawChar(controlChars[MenuChars::StartOfSelection], line, 0);
	focusedLine = line;
}