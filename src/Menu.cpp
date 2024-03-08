#include "Menu.h"

bool Menu::draw() {
	if (inSubmenu) {
		if (submenu[focusedLine]->draw()) {
			// If the submenu draws itself, we've already done our part
			return true;
		}
	}
	if (!active) {
		active = true;
	}
	String output = "";
	for (uint8_t i=0; i<numberOfItems; i++) {
		String item = submenu[i]->getTitle();
		if (i == focusedLine) {
			if (item.indexOf(MenuChar[MenuChars::StartOfSelection]) == -1) {
				item = MenuChar[MenuChars::StartOfSelection] + item + MenuChar[MenuChars::EndOfSelection];
			}
		}
	
		output += item + '\n';
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

MenuEvent::Event Menu::handleEvent(MenuEvent::Event event) {
	if (event == MenuEvent::noEvent || event == MenuEvent::lastEvent) {
		return MenuEvent::noEvent;
	}
	if (event == MenuEvent::exit || event == MenuEvent::enter) {
		return passEventToHandlerFunctions(event);
	}
	if (inSubmenu) {
		handleEvent(submenu[focusedLine]->handleEvent(event));
		return MenuEvent::noEvent;
	}
	if (event == MenuEvent::focus) {
		hasFocus = true;
	}
	if (event == MenuEvent::unfocus) {
		hasFocus = false;
	}
	return passEventToHandlerFunctions(event); 
}

MenuEvent::Event Menu::handleClick() {
	if (active == true) {
		return handleEvent(submenu[focusedLine]->handleEvent(MenuEvent::click));
	} else {
		active = true;
		return MenuEvent::enter;
	}
}

MenuEvent::Event Menu::handleBack() {
	active = false;
	return MenuEvent::exit;
}

MenuEvent::Event Menu::handleScrollNext() {
	if (focusedLine < (numberOfItems-1)) {
		setFocusedLine(focusedLine+1);
	}
	return MenuEvent::noEvent;
}

MenuEvent::Event Menu::handleScrollPrevious() {
	if (focusedLine > 0) {
		setFocusedLine(focusedLine-1);
	}
	return MenuEvent::noEvent;
}

MenuEvent::Event Menu::handleExit() {
	inSubmenu = false;
	setFocusedLine(focusedLine);
	return MenuEvent::noEvent;	
}

MenuEvent::Event Menu::handleEnter() {
	inSubmenu = true;
	return MenuEvent::noEvent;
}

void Menu::setFocusedLine(uint8_t line) {
	for (uint8_t i=0; i<numberOfOutputs; i++) {
		outputs[i].setFocusedLine(line);
	}
	if (focusedLine == line) {
		return;
	}
	submenu[focusedLine]->handleEvent(MenuEvent::unfocus);
	focusedLine = line;
	submenu[focusedLine]->handleEvent(MenuEvent::focus);
}

Menu::~Menu() {
	for (uint8_t i=0; i<numberOfItems; i++) {
		delete submenu[i];
	}
	free(submenu);
}