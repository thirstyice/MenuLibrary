#pragma once

#include "MenuOutput.h"

class MenuOutputGenericTextBased : public MenuOutput {
public:
	MenuOutputGenericTextBased() {};
	void drawLine(uint8_t line, String contents) override;
	virtual void outputLine(uint8_t line, String* contents) =0;

protected:
	void trimForOutput(String*);
	uint8_t countBreakChars(String*);
	void removeBreakChars(String*);
	virtual char getControlChar(uint8_t character) =0;
};
