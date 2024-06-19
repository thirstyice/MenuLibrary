#pragma once

#include <Arduino.h>

struct MenuChars{
public:
	enum : uint8_t {
		NoPrint,
		StartOfSelection,
		EndOfSelection,
		ReplaceableWithCursor,
		AlignRightFollowing,
		EmphasizeFollowing,
		BackArrow,
		SubmenuArrow,
		Count
	};
};
extern const char MenuChar[MenuChars::Count];

class MenuOutput {
protected:
	uint8_t width = 0;
	uint8_t height = 0;
	uint8_t focusedLine;
public:
	virtual void drawLine(uint8_t lineNumber, String contents) =0;
	virtual void setFocusedLine(uint8_t lineNumber) =0;
	uint8_t startLine;
	uint8_t getFirstLineIndex(uint8_t totalLines, uint8_t focus);
	const uint8_t getHeight() {return height;}
};