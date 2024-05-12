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
	static uint8_t focusedLine;
	static String currentContents;
	static bool contentsDidChange;
	virtual void doOutput(uint8_t startIndex, uint8_t numLines) =0;
	uint8_t width = 0;
	uint8_t height = 0;
public:
	static void setContents(String* contents);
	void draw();
	uint8_t getFirstLineIndex(uint8_t totalLines, uint8_t focus);
	const uint8_t getHeight() {return height;}
	static void setFocusedLine(uint8_t line);
};

String MenuOutput::currentContents = "Loading...";
uint8_t MenuOutput::focusedLine = 0;
bool MenuOutput::contentsDidChange = true;