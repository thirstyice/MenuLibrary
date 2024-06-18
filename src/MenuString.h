#pragma once

#include "MenuOp.h"

class MenuString final: public MenuOp {
public:
	MenuString(String _title, String* _string, uint8_t _maxLength = 255);
	void setString(String* _string);
	void setMaxLength(uint8_t _maxLength);
	String getTitle();
	bool needsRedraw();
private:
	String* string = nullptr;
	uint8_t maxLength;
	String lastValue;
	uint8_t index = 0;
	MenuEvent::Event handleClick();
	MenuEvent::Event handleBack();
	MenuEvent::Event handleScrollNext();
	MenuEvent::Event handleScrollPrevious();
};