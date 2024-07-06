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
	for (uint8_t output=0; output<numberOfOutputs; output++) {
		uint8_t startLine = outputs[output]->getFirstLineIndex(numberOfItems, focusedLine);
		uint8_t numLines = outputs[output]->getHeight();
		bool didScroll = startLine != outputs[output]->startLine;
		outputs[output]->startLine = startLine;
		for (uint8_t line=0; line<numLines; line++) {
			if (submenu[line+startLine]->needsRedraw() || didScroll || forceNextDraw) {
				outputs[output]->drawLine(line, submenu[line+startLine]->getTitle());
			}
		}
		outputs[output]->setFocusedLine(focusedLine - startLine);
	}
	forceNextDraw = false;
	return true;
}

void Menu::setOutput(MenuOutput** outputArray, uint8_t number, bool isTopLevel) {
	outputs = outputArray;
	numberOfOutputs = number;
	if (isTopLevel) {
		for (uint8_t i=0; i<numberOfOutputs; i++) {
			outputs[i]->drawLine(0, "Loading...");
		}
	}
	for (uint8_t i=0; i<numberOfItems; i++) {
		submenu[i]->setOutput(outputs, numberOfOutputs, false);
	}
}

String Menu::getTitle() {
	hasChanged = false;
	return title + MenuChar[MenuChars::SubmenuArrow];
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
		forceNextDraw = true;
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
	forceNextDraw = true;
	return MenuEvent::noEvent;	
}

MenuEvent::Event Menu::handleEnter() {
	inSubmenu = true;
	return MenuEvent::noEvent;
}

void Menu::setFocusedLine(uint8_t line) {
	if (focusedLine == line) {
		return;
	}
	submenu[focusedLine]->handleEvent(MenuEvent::unfocus);
	focusedLine = line;
	submenu[focusedLine]->handleEvent(MenuEvent::focus);
}

Menu::~Menu() {
	if (submenuShouldFree) {
	free(submenu);
	}
}