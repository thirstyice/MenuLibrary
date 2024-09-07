#include "MenuString.h"

MenuString* MenuString::setString(String* _string) {
	string = _string;
	return this;
}

MenuString* MenuString::setMaxLength(uint8_t _maxLength) {
	maxLength = _maxLength;
	if (string->length()>maxLength) {
		string->remove(maxLength);
	}
	return this;
}

String MenuString::getTitle() {
	hasChanges = false;
	String outputString = title + MenuChar[MenuChars::Break] + MenuChar[MenuChars::AlignRightFollowing];
	if (isOpen) {
		outputString += string->substring(0, index);
		outputString += MenuChar[MenuChars::StartOfSelection];
		outputString += string->charAt(index);
		outputString += MenuChar[MenuChars::EndOfSelection];
		outputString += string->substring(index+1);
	} else {
		outputString += *string;
	}
	return outputString;
}

bool MenuString::needsRedraw() {
	if (*string != lastValue) {
		lastValue = *string;
		hasChanges = true;
	}
	return hasChanges;
}

MenuReaction MenuString::engage() {
	hasChanges = true;
	if (isOpen) {
		index++;
		if (index>string->length() || (maxLength?index>maxLength:false)) {
			string->trim();
			isOpen = false;
			index = 0;
			return MenuReaction::closeDown;
		}
		return MenuReaction::noReaction;
	} else {
		index = 0;
		isOpen = true;
		return MenuReaction::openUp;
	}
}

MenuReaction MenuString::disengage() {
	hasChanges = true;
	if (isOpen) {
		if (index==0) {
			isOpen = false;
			string->trim();
			return MenuReaction::closeDown;
		}
		index--;
	}
	return MenuReaction::noReaction;
}

MenuReaction MenuString::increase() {
	if (index==string->length()) {
		*string = *string + ' ';
	}
	char newChar = string->charAt(index) + 1;
	if (newChar>126) {
		newChar = 32;
	}
	string->setCharAt(index, newChar);
	return MenuReaction::changeValue;
}

MenuReaction MenuString::decrease() {
	if (index==string->length()) {
		*string = *string + ' ';
	}
	char newChar = string->charAt(index) - 1;
	if (newChar<32) {
		newChar = 126;
	}
	string->setCharAt(index, newChar);
	return MenuReaction::changeValue;
}
