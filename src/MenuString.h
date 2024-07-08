#pragma once

#include "MenuItem.h"

class MenuString: public MenuItem {
public:
	MenuString(String _title, String* str) : MenuItem(_title), string(str) {}
	MenuString* setString(String* str);
	MenuString* setMaxLength(uint8_t len);
	String getTitle() override;
	bool needsRedraw() override;
private:
	String* string = nullptr;
	uint8_t maxLength;
	String lastValue;
	uint8_t index = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
};