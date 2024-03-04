#pragma once

#include "MenuOutput.h"
#include <LiquidCrystal_PCF8574.h>



class MenuOutputPCF8574 : public MenuOutput {
public:
	MenuOutputPCF8574(LiquidCrystal_PCF8574* lcd, uint8_t _width, uint8_t _height) : 
		lcd(lcd) {width = _width; height = _height;}
private:
	void doOutput(uint8_t startIndex, uint8_t numLines);
	LiquidCrystal_PCF8574* lcd;
};

void MenuOutputPCF8574::doOutput(uint8_t startIndex, uint8_t numLines) {
	lcd->clear();
	lcd->home();
	uint8_t startOfLine = startIndex;
	for (uint8_t i=0; i<numLines; i++) {
		uint8_t endOfLine = currentContents.indexOf('\n', startOfLine);
		String line = currentContents.substring(startOfLine, endOfLine);
		lcd->setCursor(0,i);
		if (line.charAt(0) != '\17') {
			line = " " + line;
		}
		line.replace('\17', textCursor);
		line.replace('\16', '\0');
		if (line.indexOf('\t') != -1) {
			lcd->print(line.substring(0,line.indexOf('\t')));
			lcd->rightToLeft();
			lcd->setCursor(width-1,i);
			for (uint8_t j=(line.length()-1); j>line.lastIndexOf('\t'); j--) {
				lcd->print(line[j]);
			}
			lcd->leftToRight();
		} else {
			lcd->print(line);
		}
		startOfLine = endOfLine+1;
	}
}