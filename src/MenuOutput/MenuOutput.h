#pragma once

#include <Arduino.h>

struct TitleFlags { // Indexes in title for formatting
	enum SpecialTypes {
		None,
		Submenu,
		Back
	} specialType = None;
	uint8_t selectionStart = 0; // First character in selection
	uint8_t selectionLength = 0; // Length of selection
	uint8_t alignRightFrom = 255; // First character to be aligned right
};

class MenuOutput {
protected:
	const uint8_t width;
	const uint8_t height;
	uint8_t focusedLine;
	MenuOutput(uint8_t _width, uint8_t _height) : width(_width), height(_height) {}
	void doRightAlign(const char* input, char* output, TitleFlags& flags) {
		uint8_t fillWidth = flags.specialType==TitleFlags::SpecialTypes::None?width:width-1;
		if (flags.alignRightFrom < width) {
			strncat(output, input, flags.alignRightFrom);
			uint8_t numSpaces = fillWidth-strlen(input);
			for (uint8_t i=flags.alignRightFrom; i<(flags.alignRightFrom + numSpaces); i++) {
				output[i] = ' ';
			}
			strlcat(output, &input[flags.alignRightFrom], fillWidth+1);
			if (flags.selectionStart >= flags.alignRightFrom) {
				flags.selectionStart += numSpaces;
			}
		} else {
			strlcat(output, input, fillWidth + 1);
		}
	}
public:
	virtual void drawLine(uint8_t lineNumber, const char* contents, TitleFlags flags) =0;
	virtual void setFocusedLine(uint8_t lineNumber) =0;
	uint8_t startLine;
	uint8_t getFirstLineIndex(uint8_t totalLines, uint8_t focus);
	constexpr uint8_t getHeight() {return height;}
	constexpr uint8_t getWidth() {return width;}
};