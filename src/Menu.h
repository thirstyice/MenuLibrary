#pragma once

#include "MenuOp.h"

class Menu final : public MenuOp {
public:
	bool draw();
	MenuEvent::Event handleEvent(MenuEvent::Event event); // returns true if entering / exiting a submenu
	void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel = true);
	Menu() {
		submenu = nullptr;
	}
	Menu(String _title, MenuOp** itemArray, uint8_t itemCount) {
		submenu = itemArray;
		numberOfItems = itemCount;
		title = _title;
	}
	template <class... args>
	Menu(String _title, MenuOp* arg1, args...items) {
		numberOfItems = sizeof...(items) + 1;
		MenuOp* itemArray[numberOfItems] = {arg1, items...};
		size_t memsize = numberOfItems * sizeof(MenuOp*);
		submenu = (MenuOp**)malloc(memsize);
		memcpy(submenu, itemArray, memsize);
		needsFree = true;
		title = _title;
	};
	String getTitle();
	~Menu();

protected:
	Menu(Menu& c);

private:
	void setFocusedLine(uint8_t line);
	bool needsFree = false;
	bool forceNextDraw = true;
	bool inSubmenu = false;
	uint8_t focusedLine = 0;
	MenuOutput** outputs = nullptr;
	uint8_t numberOfOutputs = 0;
	MenuEvent::Event handleClick();
	MenuEvent::Event handleBack();
	MenuEvent::Event handleEnter();
	MenuEvent::Event handleExit();
	MenuEvent::Event handleScrollNext();
	MenuEvent::Event handleScrollPrevious();
	uint8_t numberOfItems = 0;
	MenuOp** submenu;
};

