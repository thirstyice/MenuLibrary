#pragma once

#include "MenuOutput.h"

class MenuOutputGenericTextBased : public MenuOutput {
public:
	MenuOutputGenericTextBased() {};
	void drawLine(uint8_t line, String contents);
	virtual void outputLine(uint8_t line, String* contents) =0;

protected:
	virtual char getControlChar(uint8_t character) =0;
};
