#pragma once

#include "MenuItem.h"

class Menu final : public MenuItem {
public:
	bool doDraw() override;
	Menu* setOutput(MenuOutput** outputArray, uint8_t outputCount);
	Menu(MenuItem** itemArray, uint8_t itemCount) : numItems(itemCount), submenu(itemArray) {}
	template <class... args>
	Menu(MenuItem* arg1, args...items) : needsFree(true) {
		numItems = sizeof...(items) + 1;
		MenuItem* itemArray[numItems] = {arg1, items...};
		size_t memsize = numItems * sizeof(MenuItem*);
		submenu = (MenuItem**)malloc(memsize);
		memcpy(submenu, itemArray, memsize);
	};
	MenuReaction doAction(MenuAction) override;
	String getTitle() override;
	~Menu();

protected:
	Menu(Menu& c);

private:
	void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) override;
	void setFocusedLine(uint8_t line);
	bool needsFree = false;
	bool forceNextDraw = true;
	bool submenuIsOpen = false;
	uint8_t focusedLine = 0;
	MenuOutput** outputs = nullptr;
	uint8_t numOutputs = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
	uint8_t numItems = 0;
	MenuItem** submenu = nullptr;
};

