#include "Menu.h"

bool Menu::doDraw() {
	if (submenuIsOpen) {
		if (submenu[focusedLine]->doDraw()) {
			// If the submenu draws itself, we've already done our part
			return true;
		}
	}
	if (!isOpen) {
		isOpen = true;
	}
	for (uint8_t output=0; output<numOutputs; output++) {
		uint8_t startLine = outputs[output]->getFirstLineIndex(numItems, focusedLine);
		uint8_t numLines = outputs[output]->getHeight();
		bool didScroll = startLine != outputs[output]->startLine;
		outputs[output]->startLine = startLine;
		uint8_t line = 0;
		for (uint8_t item=startLine; line<numLines; line++) {
		// while (item<numItems) {
			// uint8_t hiddenType = submenu.getHidden();
			// if (hiddenType == NotHidden) {
				// break;
			// }
			// if (hiddenType == NewlyHidden) {
				// didScroll = true;
			// }
		// 	item++;
		// }
			if (item >= numItems) {
				break;
			}
			if (submenu[item]->needsRedraw() || didScroll || forceNextDraw) {
				outputs[output]->drawLine(line, submenu[item]->getTitle());
			}
			if (item==focusedLine) {
				outputs[output]->setFocusedLine(line);
			}
		}
		while (line<numLines) {
			outputs[output]->drawLine(line, "");
			line++;
		}
	}
	forceNextDraw = false;
	return true;
}

Menu* Menu::setOutput(MenuOutput** arr, uint8_t n) {
	setOutput(arr, n, true);
	return this;
}

void Menu::setOutput(MenuOutput** outputArray, uint8_t number, bool isTopLevel) {
	outputs = outputArray;
	numOutputs = number;
	if (isTopLevel) {
		for (uint8_t i=0; i<numOutputs; i++) {
			outputs[i]->drawLine(0, "Loading...");
		}
	}
}

String Menu::getTitle() {
	hasChanges = false;
	return MenuChar[MenuChars::SubmenuArrow] + title;
}
MenuReaction Menu::doAction(MenuAction action) {
	if (submenuIsOpen) {
		if (submenu[focusedLine]->doAction(action) == MenuReaction::closeDown) {
			submenuIsOpen = false;
			forceNextDraw = true;
		}
		return MenuReaction::noReaction;
	}
	return distributeAction(action);
}

MenuReaction Menu::engage() {
	if (isOpen == true) {
		MenuReaction reaction = submenu[focusedLine]->doAction(MenuAction::engage);
		switch (reaction) {
			case MenuReaction::openUp:
				submenu[focusedLine]->setOutput(outputs, numOutputs, false);
				submenuIsOpen = true;
				return MenuReaction::noReaction;
			break;
			case MenuReaction::closeDown:
				return doAction(MenuAction::disengage);
			break;
			default:
				return MenuReaction::noReaction;
			break;
		}
	} else {
		isOpen = true;
		forceNextDraw = true;
		return MenuReaction::openUp;
	}
}

MenuReaction Menu::disengage() {
	isOpen = false;
	return MenuReaction::closeDown;
}

MenuReaction Menu::increase() {
	if (focusedLine < (numItems-1)) {
		setFocusedLine(focusedLine+1);
	}
	return MenuReaction::noReaction;
}

MenuReaction Menu::decrease() {
	if (focusedLine > 0) {
		setFocusedLine(focusedLine-1);
	}
	return MenuReaction::noReaction;
}

void Menu::setFocusedLine(uint8_t line) {
	if (focusedLine == line) {
		return;
	}
	submenu[focusedLine]->doAction(MenuAction::loseFocus);
	focusedLine = line;
	submenu[focusedLine]->doAction(MenuAction::gainFocus);
}

Menu::Menu(Menu& c) :
	MenuBase(c.title),
	needsFree(c.needsFree),
	outputs(c.outputs),
	numOutputs(c.numOutputs),
	numItems(c.numItems),
	submenu(c.submenu)
{
	if (needsFree) {
		size_t memsize = numItems * sizeof(MenuCore*);
		submenu = (MenuCore**)malloc(memsize);
		memcpy(submenu, c.submenu, memsize);
	}
}

Menu::~Menu() {
	if (needsFree) {
		free(submenu);
	}
}