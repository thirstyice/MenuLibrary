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

class MenuOutputU8x8 : public MenuOutput {
protected:
	MenuOutputU8x8(uint8_t _width, uint8_t _height) :
		MenuOutput(_width, _height)
		{}
public:
	virtual void drawLine(uint8_t lineNumber, const char* contents, TitleFlags flags) =0;
	virtual void setFocusedLine(uint8_t lineNumber) =0;
};