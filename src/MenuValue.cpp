#include "MenuValue.h"


MenuEvent::Event MenuValue::handleBack() {
	if (selected == 0) {
		active = false;
		return MenuEvent::exit;
	}
	selected --;
	return MenuEvent::noEvent;
}

MenuEvent::Event MenuValue::handleClick() {
	if (!active) {
		active=true;
		selected=0;
		return MenuEvent::enter;
	} else {
		selected++;
	}
	if (selected >= size) {
		active = false;
		return MenuEvent::exit;
	}
	return MenuEvent::noEvent;
}

MenuEvent::Event MenuValue::handleScrollNext() {
	values[selected]->increment();
	return MenuEvent::noEvent;
}

MenuEvent::Event MenuValue::handleScrollPrevious() {
	values[selected]->decrement();
	return MenuEvent::noEvent;
}

String MenuValue::getTitle() const {
	String valuesString = "";
	for (uint8_t i=0; i<size; i++) {
		String variableString = values[i]->getValueAsString();
		if (active == true && selected == i) {
			variableString = String(MenuChar[MenuChars::StartOfSelection]) + variableString + String(MenuChar[MenuChars::EndOfSelection]);
		}
		valuesString += variableString + separator + String(MenuChar[MenuChars::ReplaceableWithCursor]);
	}
	valuesString.remove(valuesString.length()-2);
	return (title + MenuChar[MenuChars::AlignRightFollowing] + valuesString);
}

MenuValue::~MenuValue() {
	for (uint8_t i=0; i<size; i++) {
		delete values[i];
	}
	free(values);
}