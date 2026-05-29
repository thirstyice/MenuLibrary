#pragma once

#include "MenuOutput.h"

class MenuOutputGenericTextBased : public MenuOutput {
public:
	void drawLine(uint8_t line, const char * contents, TitleFlags flags);
	virtual void outputLine(uint8_t line, char * contents, TitleFlags flags) =0;
protected:
	char cursor;
	char submenuArrow;
	char backArrow;
	MenuOutputGenericTextBased(uint8_t _width, uint8_t _height, char _cursor, char _submenu, char _back) :
		MenuOutput(_width, _height), cursor(_cursor), submenuArrow(_submenu), backArrow(_back)
	{}

};

void MenuOutputGenericTextBased::drawLine(uint8_t lineIndex, const char* line, TitleFlags flags) {
	char lineOut[width+2] = {0};
	lineOut[0] = ((lineIndex==focusedLine)?cursor:' ');
	if (flags.specialType==TitleFlags::SpecialTypes::Back) {
		lineOut[1] = backArrow;
	}
	if (flags.alignRightFrom < width) {
		strncat(lineOut, line, flags.alignRightFrom);
		int spaceEnd = flags.alignRightFrom + (width - strlen(line));
		for (int i = flags.alignRightFrom+1; i<=spaceEnd; i++) {
			lineOut[i] = ' ';
		}
		strlcat(lineOut, &line[flags.alignRightFrom], width+2);
	} else {
		strlcat(lineOut, line, width + 2);
	}
	outputLine(lineIndex, lineOut, flags);
}
