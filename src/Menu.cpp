#include "Menu.h"

bool Menu::doDraw() {
	if (!focusedItem) {
		return false;
	}
	if (submenuIsOpen) {
		if (focusedItem->doDraw()) {
			// If the submenu draws itself, we've already done our part
			return true;
		}
	}
	if (!isOpen) {
		isOpen = true;
	}
	for (uint8_t output=0; output<numOutputs; output++) {
		uint8_t numLines = outputs[output]->getHeight();
		MenuCore* nextHead = focusedItem->getNext();
		MenuCore* prevHead = focusedItem->getPrevious();
		uint8_t numItems = 1;
		uint8_t focusPosition = numLines / 2;
		bool forward = true;
		bool noScrolling = false;
		while (numItems<numLines) {
			if (forward) {
				if (nextHead) {
					nextHead = nextHead->getNext();
					focusPosition--;
					numItems++;
				}
			} else {
				if (prevHead) {
					prevHead = prevHead->getPrevious();
					focusPosition++;
					numItems++;
				}
			}
			if (!(prevHead || nextHead)) {
				noScrolling = true;
				break;
			}
		}
		if (!noScrolling && didScroll) {
			forceNextDraw = true;
		}
		for (uint8_t line = 0; line<numLines; line++) {
			if (prevHead) {
				if (prevHead->needsRedraw() || forceNextDraw) {
					outputs[output]->drawLine(line, prevHead->getTitle());
					prevHead = prevHead->getNext();
				}
			} else {
				outputs[output]->drawLine(line, "");
			}
		}



		// bool didScroll = startLine != outputs[output]->startLine;
		// outputs[output]->startLine = startLine;
		// uint8_t drawLines = (numItems < numLines)?numItems:numLines;
		// for (uint8_t line=0; line<drawLines; line++) {
		// 	if (submenu[line+startLine]->needsRedraw() || didScroll || forceNextDraw) {
		// 		outputs[output]->drawLine(line, submenu[line+startLine]->getTitle());
		// 	}
		// }
		// if (didScroll || forceNextDraw) {
		// 	for (uint8_t line=drawLines; line<numLines; line ++) {
		// 		outputs[output]->drawLine(line, "");
		// 	}
		// }
		outputs[output]->setFocusedLine(focusPosition);
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
		if (focusedItem->doAction(action) == MenuReaction::closeDown) {
			submenuIsOpen = false;
			forceNextDraw = true;
		}
		return MenuReaction::noReaction;
	}
	return distributeAction(action);
}

MenuReaction Menu::engage() {
	if (isOpen == true) {
		MenuReaction reaction = focusedItem->doAction(MenuAction::engage);
		switch (reaction) {
			case MenuReaction::openUp:
				focusedItem->setOutput(outputs, numOutputs, false);
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
	if (focusedItem->getNext()) {
		focusedItem->doAction(MenuAction::loseFocus);
		focusedItem = focusedItem->getNext();
		focusedItem->doAction(MenuAction::gainFocus);
		didScroll = true;
	}
	return MenuReaction::noReaction;
}

MenuReaction Menu::decrease() {
	if (focusedItem->getPrevious()) {
		focusedItem->doAction(MenuAction::loseFocus);
		focusedItem = focusedItem->getPrevious();
		focusedItem->doAction(MenuAction::gainFocus);
		didScroll = true;
	}
	return MenuReaction::noReaction;
}

void Menu::setFocusedItem(MenuCore* item) {
	if (item == focusedItem) {
		return;
	}
	focusedItem->doAction(MenuAction::loseFocus);
	focusedItem = item;
	focusedItem->doAction(MenuAction::gainFocus);
	forceNextDraw = true;
}
