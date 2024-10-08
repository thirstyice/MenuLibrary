#include "MenuOutput.h"

const char MenuChar[MenuChars::Count] = {
	127 , // Do not print
	'\17', // Start of selection
	'\16', // End of selection
	'\32', // Previous character may be replaced by cursor at start of selection
	'\t' , // Rest of line should align right
	'\1' , // Rest of line should be emphasized (if possible)
	'\10', // Back arrow
	'\14', // Submenu indicator arrow
	'\n' , // Break location
};

uint8_t MenuOutput::getFirstLineIndex(uint8_t totalLines, uint8_t focus) {
	if (totalLines<height) {
		return 0;
	}
	uint8_t middle = height>>1;
	uint8_t firstLine = focus-middle;
	if (focus < middle) {
		firstLine = 0;
	} else if (focus > (totalLines-middle)) {
		firstLine = totalLines - height;
	}
	return firstLine;
}