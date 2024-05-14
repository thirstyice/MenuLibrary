#include "MenuOutput.h"

const char MenuChar[MenuChars::Count] = {
	'\0' , // Null, do not print
	'\17', // Start of selection
	'\16', // End of selection
	'\32', // Previous character may be replaced by cursor at start of selection
	'\t' , // Rest of line should align right
	'\1' , // Rest of line should be emphasized (if possible)	
	'\10',  // Back arrow
};

String MenuOutput::currentContents = "Loading...\n";
uint8_t MenuOutput::focusedLine = 0;
bool MenuOutput::contentsDidChange = true;

void MenuOutput::setContents(String* contents) {
	if (currentContents == *contents || *contents == "") {
		return;
	}
	currentContents = *contents;
	contentsDidChange = true;
}

void MenuOutput::setFocusedLine(uint8_t line) {
	if (focusedLine == line) {
		return;
	}
	focusedLine = line;
	contentsDidChange = true;
}

void MenuOutput::draw() {
	if (contentsDidChange == true) {
		contentsDidChange = false;
		uint8_t numLines = 0;
		for (uint8_t i=0; i<currentContents.length(); i++) {
			if (currentContents.charAt(i) == '\n') {
				numLines++;
			}
		}
		uint8_t lineStart[numLines];
		uint8_t firstIndex = 0;
		for (uint8_t i=0; i<numLines; i++) {
			lineStart[i] = firstIndex;
			firstIndex = currentContents.indexOf('\n',firstIndex) +1;
		}
		if (numLines<=height || height == 0) {
			doOutput(0, numLines);
		} else {
			doOutput(lineStart[getFirstLineIndex(numLines, focusedLine)], height);
		}
	}
}

uint8_t MenuOutput::getFirstLineIndex(uint8_t totalLines, uint8_t focus) {
	uint8_t middle = height>>1;
	uint8_t firstLine = focus-middle;
	if (focus < middle) {
		firstLine = 0;
	} else if (focusedLine > (totalLines-middle)) {
		firstLine = totalLines - height;
	}
	return firstLine;
}