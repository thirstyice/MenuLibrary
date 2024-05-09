#include "MenuString.h"

MenuString::MenuString(String _title, String* _string) {
	title = _title;
	setString(_string);
}

void MenuString::setString(String* _string) {
	string = _string;
}

String MenuString::getTitle() const {
	String outputString = "";
	outputString += string->substring(0, index-1);
	outputString += '\17';
	outputString += string->charAt(index);
	outputString += '\16';
	outputString += string->substring(index+1);
	return (active?title + '\t':"") + outputString;
}


MenuEvent::Event MenuString::handleClick() {
	if (active) {
		index++;
		if (index>string->length()) {
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
	if (active) {
		if (index==0) {
			active = false;
			string->trim();
			return MenuEvent::exit;
		}
		index--;
		return MenuEvent::noEvent;
	}
}

MenuEvent::Event MenuString::handleScrollNext() {
	char newChar = string->charAt(index) + 1;
	if (newChar>126) {
		newChar = 32;
	}
	string->setCharAt(index, newChar);
}

MenuEvent::Event MenuString::handleScrollPrevious() {
	char newChar = string->charAt(index) - 1;
	if (newChar<32) {
		newChar = 126;
	}
	string->setCharAt(index, newChar);
}
