#include "MenuOutput.h"

void MenuOutput::setContents(String contents) {
	if (currentContents == contents) {
		return;
	}
	currentContents = contents;
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
			return;
		}
		
		uint8_t middle = height>>1;
		if (focusedLine < middle) {
			doOutput(lineStart[0], height);
		} else if (focusedLine > (numLines - middle)) {
			doOutput(lineStart[numLines-height], height);
		} else {
			doOutput(lineStart[focusedLine-middle], height);
		}
	}
}