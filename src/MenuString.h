#pragma once

#include "MenuBase.h"

class MenuString: public MenuBase<MenuString> {
public:
	MenuString(const char* _title, String& str) : MenuBase(_title), string(str) {}
	MenuString& setString(String& str);
	MenuString& setMaxLength(uint8_t len);
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
	bool needsRedraw() override;
private:
	String& string;
	uint8_t maxLength=0;
	String lastValue;
	uint8_t index = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
};