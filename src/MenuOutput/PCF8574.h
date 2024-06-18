#pragma once

#include "MenuOutput.h"
#include <LiquidCrystal_PCF8574.h>



class MenuOutputPCF8574 : public MenuOutput {
public:
	MenuOutputPCF8574(LiquidCrystal_PCF8574* _lcd, uint8_t _width, uint8_t _height) : 
		lcd(_lcd) {width = _width; height = _height;}
	void setCursor(unsigned char newCursor) {textCursor = newCursor;};
	void drawLine(uint8_t line, String contents);
	void setFocusedLine(uint8_t line);

private:
	unsigned char textCursor = 126;
	LiquidCrystal_PCF8574* lcd;
};


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
	bool isSubmenu = line.endsWith(String(MenuChar[MenuChars::SubmenuArrow]));
	for (uint8_t character=0; character<MenuChars::Count; character++) {
		characterIndex = line.indexOf(MenuChar[character]);
		if (character==MenuChars::AlignRightFollowing) {
			// We want to keep the first right-align marker for use later, but the rest can be discarded
			characterIndex = line.indexOf(MenuChar[character], characterIndex + 1);
		}
		while (characterIndex != -1) {
			if (characterIndex == (int)line.length()) {
				// That's the null at the end of the string, don't delete that!
				break;
			}
			line.remove(characterIndex, 1);
			characterIndex = line.indexOf(MenuChar[character]);
		}
	}
	uint8_t alignRightFrom = line.indexOf(MenuChar[MenuChars::AlignRightFollowing]);
	line.remove(alignRightFrom, 1);
	lcd->setCursor(0, lineIndex);
	lcd->print((lineIndex==focusedLine)?(char)textCursor:' ');
	if (width > (line.length()+isSubmenu) && alignRightFrom != (uint8_t)-1) {
		lcd->print(line.substring(0, alignRightFrom));
		for (uint8_t i=line.length(); i<width; i++) {
			lcd->print(' ');
		}
		lcd->rightToLeft();
		lcd->setCursor(width-1, lineIndex);
		if (isSubmenu) {
			line += (char)126;
		}
		for (uint8_t j=(line.length()-1); j>=alignRightFrom; j--) {
			lcd->print(line[j]);
		}
		lcd->leftToRight();
	} else {
		lcd->print(line.substring(0,width-1));
		for (uint8_t i=line.length(); i<width; i++) {
			lcd->print(' ');
		}
		if (isSubmenu) {
			lcd->setCursor(width-1, lineIndex);
			lcd->write(126);
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