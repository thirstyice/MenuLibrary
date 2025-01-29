#include "MenuValue.h"

MenuValues::MenuValues(const char* _title, MenuCore* after, MenuValueOp* firstElement) :
	MenuBase(_title, after),
	selected(firstElement)
{}

MenuReaction MenuValues::disengage() {
	hasChanges = true;
	if (selected->getPrev()) {
		selected = selected->getPrev();
		return MenuReaction::noReaction;
	}
	isOpen = false;
	return MenuReaction::closeDown;
}

MenuReaction MenuValues::engage() {
	hasChanges = true;
	if (!isOpen) {
		isOpen=true;
		return MenuReaction::openUp;
	}
	if (selected->getNext()) {
		selected = selected->getNext();
		return MenuReaction::noReaction;
	}
	isOpen = false;
	while (selected->getPrev()) {
		selected = selected->getPrev();
	}
	return MenuReaction::closeDown;
}

MenuReaction MenuValues::increase() {
	selected->increment();
	return MenuReaction::changeValue;
}

MenuReaction MenuValues::decrease() {
	selected->decrement();
	return MenuReaction::changeValue;
}

String MenuValues::getTitle() {
	hasChanges = false;
	String valuesString = "";
	MenuValueOp* ptr = selected;
	while (ptr->getPrev()) {
		ptr = ptr->getPrev();
	}
	while (ptr->getNext()) {
		String variableString = ptr->getValueAsString();
		if (isOpen == true && selected == ptr) {
			variableString = String(MenuChar[MenuChars::StartOfSelection]) + variableString + String(MenuChar[MenuChars::EndOfSelection]);
		}
		valuesString += variableString + MenuChar[MenuChars::Break] + separator + String(MenuChar[MenuChars::ReplaceableWithCursor]);
		ptr = ptr->getNext();
	}
	valuesString.remove(valuesString.length()-3); // The trailing separator
	return (_getTitle() + MenuChar[MenuChars::Break] + MenuChar[MenuChars::AlignRightFollowing] + valuesString);
}

MenuValues* MenuValues::setSeparator(char _separator) {
	separator = _separator;
	hasChanges = true;
	return this;
}

bool MenuValues::needsRedraw() {
	if (hasChanges) {
		return true;
	}
	MenuValueOp* ptr = selected;
	while (ptr->getPrev()) {
		if (ptr->valueHasChanged() == true) {
			return true;
		}
		ptr = ptr->getPrev();
	}
	ptr = selected;
	while (ptr->getNext()) {
		if (ptr->valueHasChanged()) {
			return true;
		}
	}
	return false;
}