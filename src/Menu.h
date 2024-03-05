#pragma once

#include <Arduino.h>
#include "MenuOp.h"
#include "MenuItem.h"

class Menu : public MenuOp {
public:
	bool draw();
	void setCursor(char cursor);
	bool handleEvent(Event event); // returns true if entering / exiting a submenu
	void setOutput(MenuOutput* outputArray, uint8_t outputCount);
	template <class... args>
	Menu(String _title, args...items) : submenu{items...} {
		numberOfItems = sizeof...(items);
		title = _title;
		handleEvent(enter);
	};
	~Menu();

	
private:
	void setFocusedLine(uint8_t line);
	bool inSubmenu = false;
	uint8_t focusedLine = 0;
	MenuOutput* outputs = {nullptr};
	uint8_t numberOfOutputs = 0;
	virtual bool handleClick();
	virtual bool handleEnter();
	virtual bool handleExit();
	virtual bool handleScrollNext();
	virtual bool handleScrollPrevious();
	uint8_t numberOfItems;
	MenuOp* submenu[];
};

