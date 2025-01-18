#pragma once

#include "MenuBase.h"

class Menu final : public MenuBase<Menu> {
public:
	bool doDraw() override;
	Menu* setOutput(MenuOutput** outputArray, uint8_t outputCount);
	using MenuBase<Menu>::MenuBase;
	Menu(const char* _title, MenuCore* _focusedItem) : MenuBase(_title), focusedItem(_focusedItem) {}
	Menu(const char* _title, MenuCore* after, MenuCore* _focusedItem) : MenuBase(_title, after), focusedItem(_focusedItem) {}
	MenuReaction doAction(MenuAction) override;
	String getTitle() override;
	void setFocusedItem(MenuCore* item);
private:
	void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) override;
	bool forceNextDraw = true;
	bool submenuIsOpen = false;
	bool didScroll = false;
	MenuCore* focusedItem = nullptr;
	MenuOutput** outputs = nullptr;
	uint8_t numOutputs = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
};
