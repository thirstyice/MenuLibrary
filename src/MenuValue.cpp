#include "MenuValue.h"


MenuReaction MenuValue::disengage() {
	hasChanges = true;
	if (selected == 0) {
		isOpen = false;
		return MenuReaction::closeDown;
	}
	selected --;
	return MenuReaction::noReaction;
}

MenuReaction MenuValue::engage() {
	hasChanges = true;
	if (!isOpen) {
		isOpen=true;
		selected=0;
		return MenuReaction::openUp;
	} else {
		selected++;
	}
	if (selected >= size) {
		isOpen = false;
		return MenuReaction::closeDown;
	}
	return MenuReaction::noReaction;
}

MenuReaction MenuValue::increase() {
	values[selected]->increment();
	return MenuReaction::changeValue;
}

MenuReaction MenuValue::decrease() {
	values[selected]->decrement();
	return MenuReaction::changeValue;
}

String MenuValue::getTitle() {
	hasChanges = false;
	String valuesString = "";
	for (uint8_t i=0; i<size; i++) {
		String variableString = values[i]->getValueAsString();
		if (isOpen == true && selected == i) {
			variableString = String(MenuChar[MenuChars::StartOfSelection]) + variableString + String(MenuChar[MenuChars::EndOfSelection]);
		}
		valuesString += variableString + separator + String(MenuChar[MenuChars::ReplaceableWithCursor]);
	}
	valuesString.remove(valuesString.length()-2);
	return ((isOpen?"":title) + MenuChar[MenuChars::AlignRightFollowing] + valuesString);
}

MenuValue* MenuValue::setSeparator(char _separator) {
	separator = _separator;
	hasChanges = true;
	return this;
}

bool MenuValue::needsRedraw() {
	for (uint8_t i=0; i<size; i++) {
		if (values[i]->valueHasChanged() == true) {
			hasChanges = true;
		}
	}
	return hasChanges;
}

MenuValue::~MenuValue() {
	for (uint8_t i=0; i<size; i++) {
		delete values[i];
	}
	free(values);
}