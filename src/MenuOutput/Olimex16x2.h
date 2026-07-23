#pragma once

#include "GenericTextBased.h"
#include <Olimex16x2.h>

class MenuOutputOlimex16x2 : public MenuOutputGenericTextBased {
public:
	MenuOutputOlimex16x2(Olimex16x2* _lcd) :
		MenuOutputGenericTextBased(15, 2, 126, 126, 127), // Width less cursor
		lcd(_lcd)
	{}
	void setCursor(char newCursor) {cursor=newCursor;};
	void outputLine(uint8_t line, char* contents, TitleFlags flags);
private:
	Olimex16x2* lcd;
};

void MenuOutputOlimex16x2::outputLine(uint8_t lineIndex, char* line, TitleFlags flags) {
	if (flags.selectionLength > 0) {
		line[flags.selectionStart] = cursor;
	}
	lcd->drawLine(lineIndex, line);
}
