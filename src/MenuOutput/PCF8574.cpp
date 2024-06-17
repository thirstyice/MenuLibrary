#include "PCF8574.h"



void MenuOutputPCF8574::drawLine(uint8_t lineIndex, String line) {
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
	lcd->setCursor(0, lineIndex);
	lcd->print((lineIndex==focusedLine)?(char)textCursor:' ');
	if (width > line.length() && alignRightFrom != -1) {
		lcd->print(line.substring(0, alignRightFrom));
		for (uint8_t i=line.length(); i<width; i++) {
			lcd->print(' ');
		}
		lcd->rightToLeft();
		lcd->setCursor(width-1, lineIndex);
		for (uint8_t j=(line.length()-1); j>alignRightFrom; j--) {
			lcd->print(line[j]);
		}
		lcd->leftToRight();
	} else {
		lcd->print(line);
		for (uint8_t i=line.length(); i<width; i++) {
			lcd->print(' ');
		}
	}
}

void MenuOutputPCF8574::setFocusedLine(uint8_t line) {
	if (line==focusedLine) {
		return;
	}
	lcd->setCursor(0, focusedLine);
	lcd->print(' ');
	lcd->setCursor(0, line);
	lcd->print((char)textCursor);
	focusedLine = line;
}