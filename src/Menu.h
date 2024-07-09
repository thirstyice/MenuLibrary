#pragma once

#include "MenuBase.h"

class Menu final : public MenuBase<Menu> {
public:
	bool doDraw() override;
	Menu* setOutput(MenuOutput** outputArray, uint8_t outputCount);
	Menu(String _title, MenuCore** itemArray, uint8_t itemCount) : MenuBase(_title), numItems(itemCount), submenu(itemArray) {}
	template <class... args>
	Menu(String _title, MenuCore* arg1, args...items) : MenuBase(_title), needsFree(true) {
		numItems = sizeof...(items) + 1;
		MenuCore* itemArray[numItems] = {arg1, items...};
		size_t memsize = numItems * sizeof(MenuCore*);
		submenu = (MenuCore**)malloc(memsize);
		memcpy(submenu, itemArray, memsize);
	};
	template <class... args>
	Menu(MenuCore* arg1, args...items) : Menu("-", arg1, items...) {}
	Menu(MenuCore** itemArray, uint8_t count) : Menu("-", itemArray, count) {}
	Menu() : Menu((MenuCore**)nullptr, 0) {}
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
	MenuCore** submenu = nullptr;
};
