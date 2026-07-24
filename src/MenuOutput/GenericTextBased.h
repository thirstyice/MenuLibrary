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
	lineOut[0] = (flags.focusedLine?cursor:' ');
	doRightAlign(line, lineOut+1, flags); // +1 beacuse cursor
	for (uint8_t i=strlen(lineOut); i<width; i++) {
		lineOut[i] = ' ';
	}
	if (flags.specialType==TitleFlags::SpecialTypes::Submenu) {
		lineOut[width] = submenuArrow;
	} else if (flags.specialType == TitleFlags::SpecialTypes::Back) {
		lineOut[width]=backArrow;
	}
	outputLine(lineIndex, lineOut, flags);
}
