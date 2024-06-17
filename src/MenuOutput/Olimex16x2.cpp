#include "Olimex16x2.h"


void MenuOutputOlimex16x2::doOutput(uint8_t startIndex, uint8_t numLines) {
	lcd->clear();
	uint8_t startOfLine = startIndex;
	for (uint8_t i=0; i<numLines; i++) {
		uint8_t endOfLine = currentContents.indexOf('\n', startOfLine);
		String line = currentContents.substring(startOfLine, endOfLine);
		if (line.charAt(0) != MenuChar[MenuChars::StartOfSelection]) {
			line = " " + line;
		}
		line.replace(MenuChar[MenuChars::BackArrow], (char)127);
		int characterIndex = line.indexOf(MenuChar[MenuChars::StartOfSelection]);
		while (characterIndex != -1) {
			line[characterIndex] = textCursor;
			if (characterIndex!=0 && line.charAt(characterIndex-1)==MenuChar[MenuChars::ReplaceableWithCursor]) {
				line.remove(characterIndex-2,2);
			}
			characterIndex = line.indexOf(MenuChar[MenuChars::StartOfSelection]);
		}
		uint8_t alignRightFrom = line.indexOf(MenuChar[MenuChars::AlignRightFollowing]);
		line.replace(MenuChars::AlignRightFollowing, ' ');
		for (uint8_t character=0; character<MenuChars::Count; character++) {
			characterIndex = line.indexOf(MenuChar[character]);
			while (characterIndex != -1) {
				if (characterIndex == (int)line.length()) {
					// That's the null at the end of the string, don't delete that!
					break;
				}
				line.remove(characterIndex, 1);
				characterIndex = line.indexOf(MenuChar[character]);
			}
		}
		if (width > line.length() && alignRightFrom != -1) {
			lcd->drawLine(i, line.substring(0, alignRightFrom));
			uint8_t position = width;
			for (uint8_t j=(line.length()-1); j>=alignRightFrom; j--) {
				position--;
				lcd->drawChar(line[j], i, position);
			}
		} else {
			lcd->drawLine(i, line);
		}
		startOfLine = endOfLine+1;
	}
}