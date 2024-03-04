#pragma once

#include <Arduino.h>
#include "MenuOp.h"
#include "MenuItem.h"

template <uint8_t numberOfItems> class Menu : public MenuOp {
public:
	bool draw();
	void setCursor(char cursor);
	bool handleEvent(Event event); // returns true if entering / exiting a submenu
	void setOutput(MenuOutput* outputArray, uint8_t outputCount);
	template <class... args>
	Menu(String _title, args...items) : submenu{items...} {
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
	MenuOp* submenu[];
};


template <uint8_t numberOfItems>
bool Menu<numberOfItems>::draw() {
	if (inSubmenu) {
		if (submenu[focusedLine]->draw()) {
			// If the submenu draws itself, we've already done our part
			return true;
		}
	}
	String output = "";
	for (uint8_t i=0; i<numberOfItems; i++) {
		String item = submenu[i]->getTitle();
		if (i == focusedLine) {
			if (item.indexOf('\17') == -1) {
				item = '\17' + item + '\16';
			}
		}
		output += item + '\n';;
	}
	for (uint8_t i=0; i<numberOfOutputs; i++) {
		outputs[i].setContents(output);
		outputs[i].draw();
	}
	return true;
}

template <uint8_t numberOfItems>
void Menu<numberOfItems>::setOutput(MenuOutput* outputArray, uint8_t number) {
	outputs = outputArray;
	numberOfOutputs = number;
	for (uint8_t i=0; i<numberOfItems; i++) {
		submenu[i]->setOutput(outputs, numberOfOutputs);
	}
}

template <uint8_t numberOfItems>
void Menu<numberOfItems>::setCursor(char cursor) {
	for (uint8_t i=0; i<numberOfOutputs; i++) {
		outputs[i].textCursor(cursor);
	}
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleEvent(Event event) {
	if (inSubmenu) {
		if (submenu[focusedLine]->handleEvent(event) && event == exit) {
			inSubmenu = false;
			setFocusedLine(focusedLine);
		}
		return false;
	}
	if (event == focus) {
		hasFocus = true;
	}
	if (event == unfocus) {
		hasFocus = false;
	}
	return passEventToHandlerFunctions(event); 
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleClick() {
	if (submenu[focusedLine]->handleEvent(enter) == true) {
		inSubmenu = true;
	} else {
		submenu[focusedLine]->handleEvent(click);
	}
	return false;
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleScrollNext() {
	if (focusedLine < (numberOfItems-1)) {
		setFocusedLine(focusedLine+1);
	}
	return false;
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleScrollPrevious() {
	if (focusedLine > 0) {
		setFocusedLine(focusedLine-1);
	}
	return false;
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleExit() {
	return true;	
}

template <uint8_t numberOfItems>
bool Menu<numberOfItems>::handleEnter() {
	setFocusedLine(0);
	return true;
}

template <uint8_t numberOfItems>
void Menu<numberOfItems>::setFocusedLine(uint8_t line) {
	for (uint8_t i=0; i<numberOfOutputs; i++) {
		outputs[i].setFocusedLine(focusedLine);
	}
	if (focusedLine == line) {
		return;
	}
	submenu[focusedLine]->handleEvent(unfocus);
	focusedLine = line;
	submenu[focusedLine]->handleEvent(focus);
}

template <uint8_t numberOfItems>
Menu<numberOfItems>::~Menu() {
	for (uint8_t i=0; i<numberOfItems; i++) {
		delete submenu[i];
	}
}