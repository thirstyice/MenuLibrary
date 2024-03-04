#pragma once

#include <Arduino.h>

class MenuOutput {
protected:
	uint8_t focusedLine = 0;
	String currentContents = "";
	bool contentsDidChange = false;
	virtual void doOutput(uint8_t startIndex, uint8_t numLines) =0;
	uint8_t width = 0;
	uint8_t height = 0;
	char textCursor = '>';
public:
	void setContents(String contents);
	void setCursor(char newCursor) {textCursor = newCursor;};

	void draw();
	void setFocusedLine(uint8_t line);
};
