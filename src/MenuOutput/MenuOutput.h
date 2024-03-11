#pragma once

#include <Arduino.h>

struct MenuChars{
public:
	enum : uint8_t {
		Null,
		StartOfSelection,
		EndOfSelection,
		ReplaceableWithCursor,
		AlignRightFollowing,
		EmphasizeFollowing,
		BackArrow,
		Count
	};
};
extern const char MenuChar[MenuChars::Count];

class MenuOutput {
protected:
	uint8_t focusedLine = 0;
	String currentContents = "";
	bool contentsDidChange = false;
	virtual void doOutput(uint8_t startIndex, uint8_t numLines) =0;
	uint8_t width = 0;
	uint8_t height = 0;
public:
	void setContents(String contents);
	void draw();
	void setFocusedLine(uint8_t line);
};