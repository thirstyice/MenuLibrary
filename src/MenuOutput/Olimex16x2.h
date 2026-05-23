#pragma once

#include "GenericTextBased.h"
#include <Olimex16x2.h>

class MenuOutputOlimex16x2 : public MenuOutputGenericTextBased {
public:
	MenuOutputOlimex16x2(Olimex16x2* _lcd) :
		lcd(_lcd) {width = 16; height = 2;}
	void setCursor(char newCursor) {cursor=newCursor;};
	void outputLine(uint8_t line, const char* contents);
	void setFocusedLine(uint8_t line);
private:
	char cursor = 126;
	char backArrow = 127;
	char submenuArrow = 126;
	Olimex16x2* lcd;
};

void MenuOutputOlimex16x2::outputLine(uint8_t lineIndex, const char* line, TitleFlags flags) {
	bool isSubmenu = line[0] == MenuChars::SubmenuArrow;
	if (isSubmenu) {
		line = &line[1];
	}
	char lineOut[width+1];
	lineOut[0] = (lineIndex==focusedLine?cursor:' ');
	if (flags.alignRightFrom < width) {
		strncat(lineOut, line, flags.alignRightFrom);
	}
	strlcat(lineOut, line, min(width+1, flags.alignRightFrom));
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