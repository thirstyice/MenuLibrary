#pragma once

#include "MenuBase.h"

class MenuString: public MenuBase {
public:
	MenuString(const char* _title, MenuCore* after, String* str) : MenuBase(_title, after), string(str) {}
	MenuString* setString(String* str);
	MenuString* setMaxLength(uint8_t len);
	String getTitle() override;
	bool needsRedraw() override;
private:
	String* string = nullptr;
	uint8_t maxLength=0;
	String lastValue;
	uint8_t index = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
};