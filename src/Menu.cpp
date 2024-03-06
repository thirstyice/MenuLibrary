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

MenuOp::Event Menu::handleEvent(Event event) {
	if (event == noEvent || event == lastEvent) {
		return noEvent;
	}
	if (event == exit || event == enter) {
		return passEventToHandlerFunctions(event);
	}
	if (inSubmenu) {
		handleEvent(submenu[focusedLine]->handleEvent(event));
		return noEvent;
	}
	if (event == focus) {
		hasFocus = true;
	}
	if (event == unfocus) {
		hasFocus = false;
	}
	return passEventToHandlerFunctions(event); 
}

MenuOp::Event Menu::handleClick() {
	if (active) {
		handleEvent(submenu[focusedLine]->handleEvent(click));
		return noEvent;
	} else {
		active = true;
		return enter;
	}
}

MenuOp::Event Menu::handleBack() {
	return exit;
}

MenuOp::Event Menu::handleScrollNext() {
	if (focusedLine < (numberOfItems-1)) {
		setFocusedLine(focusedLine+1);
	}
	return noEvent;
}

MenuOp::Event Menu::handleScrollPrevious() {
	if (focusedLine > 0) {
		setFocusedLine(focusedLine-1);
	}
	return noEvent;
}

MenuOp::Event Menu::handleExit() {
	inSubmenu = false;
	setFocusedLine(focusedLine);
	return noEvent;	
}

MenuOp::Event Menu::handleEnter() {
	inSubmenu = true;
	return noEvent;
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
	free(submenu);
}