#pragma once

#include <Arduino.h>

struct MenuChars{	enum : char {
	BackArrow = '\10',
};};

struct TitleFlags { // Indexes in title for formatting
	uint8_t selectionStart = 0; // First character in selection
	uint8_t selectionLength = 0; // Length of selection
	uint8_t alignRightFrom = 255; // First character to be aligned right
	uint8_t replaceableWithCursor[5] = {255, 255, 255, 255, 255};
	bool isSubmenu = false;
};

class MenuOutput {
protected:
	const uint8_t width;
	const uint8_t height;
	uint8_t focusedLine;
	MenuOutput(uint8_t _width, uint8_t _height) : width(_width), height(_height) {}
public:
	virtual void drawLine(uint8_t lineNumber, const char* contents, TitleFlags flags) =0;
	virtual void setFocusedLine(uint8_t lineNumber) =0;
	uint8_t startLine;
	uint8_t getFirstLineIndex(uint8_t totalLines, uint8_t focus);
	constexpr uint8_t getHeight() {return height;}
	constexpr uint8_t getWidth() {return width;}
};