#include "MenuString.h"

MenuString::MenuString(String _title, String* _string, uint8_t _maxLength) {
	title = _title;	
	setString(_string);
	setMaxLength(_maxLength);
}

void MenuString::setString(String* _string) {
	string = _string;
}

void MenuString::setMaxLength(uint8_t _maxLength) {
	maxLength = _maxLength;
	if (string->length()>maxLength) {
		string->remove(maxLength);
	}
}

String MenuString::getTitle() {
	hasChanged = false;
	String outputString = "";
	if (active) {
		outputString += string->substring(0, index);
		outputString += MenuChar[MenuChars::StartOfSelection];
		outputString += string->charAt(index);
		outputString += MenuChar[MenuChars::EndOfSelection];
		outputString += string->substring(index+1);
	} else {
		outputString = title + '\t' + *string;
	}
	return outputString;
}

bool MenuString::needsRedraw() {
	if (*string != lastValue) {
		lastValue = *string;
		hasChanged = true;
	}
	return hasChanged;
}

MenuEvent::Event MenuString::handleClick() {
	hasChanged = true;
	if (active) {
		index++;
		if (index>string->length() || index>maxLength) {
			active = false;
			index = 0;
			return MenuEvent::exit;
		}
		return MenuEvent::noEvent;
	} else {
		index = 0;
		active = true;
		return MenuEvent::enter;
	}
}

MenuEvent::Event MenuString::handleBack() {
	hasChanged = true;
	if (active) {
		if (index==0) {
			active = false;
			string->trim();
			return MenuEvent::exit;
		}
		index--;
	}
	return MenuEvent::noEvent;
}

MenuEvent::Event MenuString::handleScrollNext() {
	if (index==string->length()) {
		*string = *string + ' ';
	}
	char newChar = string->charAt(index) + 1;
	if (newChar>126) {
		newChar = 32;
	}
	string->setCharAt(index, newChar);
	return MenuEvent::noEvent;
}

MenuEvent::Event MenuString::handleScrollPrevious() {
	if (index==string->length()) {
		*string = *string + ' ';
	}
	char newChar = string->charAt(index) - 1;
	if (newChar<32) {
		newChar = 126;
	}
	string->setCharAt(index, newChar);
	return MenuEvent::noEvent;
}
