#include "Menu.h"



bool Menu::draw() {
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

void Menu::setOutput(MenuOutput* outputArray, uint8_t number) {
	outputs = outputArray;
	numberOfOutputs = number;
	for (uint8_t i=0; i<numberOfItems; i++) {
		submenu[i]->setOutput(outputs, numberOfOutputs);
	}
}

void Menu::setCursor(char cursor) {
	for (uint8_t i=0; i<numberOfOutputs; i++) {
		outputs[i].setCursor(cursor);
	}
}

bool Menu::handleEvent(Event event) {
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

bool Menu::handleClick() {
	if (submenu[focusedLine]->handleEvent(enter) == true) {
		inSubmenu = true;
	} else {
		submenu[focusedLine]->handleEvent(click);
	}
	return false;
}

bool Menu::handleScrollNext() {
	if (focusedLine < (numberOfItems-1)) {
		setFocusedLine(focusedLine+1);
	}
	return false;
}

bool Menu::handleScrollPrevious() {
	if (focusedLine > 0) {
		setFocusedLine(focusedLine-1);
	}
	return false;
}

bool Menu::handleExit() {
	return true;	
}

bool Menu::handleEnter() {
	setFocusedLine(0);
	return true;
}

void Menu::setFocusedLine(uint8_t line) {
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

Menu::~Menu() {
	for (uint8_t i=0; i<numberOfItems; i++) {
		delete submenu[i];
	}
}