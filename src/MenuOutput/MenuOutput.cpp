#include "MenuOutput.h"

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