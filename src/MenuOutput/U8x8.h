/*******************************************************************************
* Project: MenuLibrary                                                         *
* Filename: /src/MenuOutput/U8x8.h                                             *
*                                                                              *
* Created: 2026-06-20                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see MenuLibrary/LICENSE (if applicable)                          *
*                                                                              *
*******************************************************************************/

#include "MenuOutput.h"
#include <U8x8lib.h>

class MenuOutputU8x8 : public MenuOutput {
private:
	U8X8* u8x8;
	const uint8_t* font;
public:
	MenuOutputU8x8(U8X8* _u8x8, const uint8_t* _font) :
		MenuOutput(_u8x8->getCols(), _u8x8->getRows()),
		u8x8(_u8x8),
		font(_font)
	{}
	void drawLine(uint8_t lineNumber, const char* contents, TitleFlags flags);
};

void MenuOutputU8x8::drawLine(uint8_t lineNumber, const char* contents, TitleFlags flags) {
	char output[width+1] = {0};
	u8x8->clearLine(lineNumber);
	doRightAlign(contents, output, flags);

	u8x8->setFont(font);

	if (flags.focusedLine) {
		u8x8->setInverseFont(1);
		uint8_t position = 0;
		for (; position<flags.selectionStart; position++) {
			if (output[position]=='\0') {
				break;
			}
			u8x8->drawGlyph(position, lineNumber, output[position]);
		}
		u8x8->setInverseFont(0);
		for (; position<(flags.selectionStart+flags.selectionLength); position++) {
			if (output[position]=='\0') {
				break;
			}
			u8x8->drawGlyph(position, lineNumber, output[position]);
		}
		u8x8->setInverseFont(1);
		for (;;position++) {
			if (output[position]=='\0') {
				break;
			}
			u8x8->drawGlyph(position, lineNumber, output[position]);
		}
	} else {
		u8x8->setInverseFont(0);
		u8x8->drawString(0, lineNumber, output);
	}

	u8x8->setFont(u8x8_font_open_iconic_arrow_1x1);
	if (flags.specialType == TitleFlags::SpecialTypes::Submenu) {
		u8x8->drawGlyph(width-1, lineNumber, 77);
	} else if (flags.specialType == TitleFlags::SpecialTypes::Back) {
		u8x8->drawGlyph(width-1, lineNumber, 78);
	}
}