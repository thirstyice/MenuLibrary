#include "MenuString.h"

MenuString& MenuString::setString(String& _string) {
	string = _string;
	return *this;
}

MenuString& MenuString::setMaxLength(uint8_t _maxLength) {
	maxLength = _maxLength;
	if (string.length()>maxLength) {
		string.remove(maxLength);
	}
	return *this;
}

MenuCore::TitleFlags MenuString::getTitle(char * buf, const uint8_t& len) {
	hasChanges = false;
	TitleFlags flags;
	const char * temp;

	// Title

	uint8_t testLen = strlen(title);
	if (len<(testLen + string.length()) && isOpen) {
		temp = &title[testLen-1];
	} else {
		temp = title;
	}
	strcpy(buf, temp);
	flags.alignRightFrom = strlen(buf);

	// Value

	testLen = (len-flags.alignRightFrom)/2;
	temp = string.c_str();
	if (string.length()>=(testLen*2) && isOpen && index>testLen) {
		uint8_t offset;
		if (index + (testLen) > string.length()) {
			uint8_t offset = string.length() - (testLen*2);
		} else {
			offset = (index-(testLen));
		}
		temp += offset;
		strlcat(buf, temp, len);
		flags.selectionStart = flags.alignRightFrom + (index-offset);
	} else {
		strlcat(buf, string.c_str(), len);
		flags.selectionStart = flags.alignRightFrom + index;
	}
	if (isOpen) {
		flags.selectionLength = 1;
	}

	return flags;
}

bool MenuString::needsRedraw() {
	if (string != lastValue) {
		lastValue = string;
		hasChanges = true;
	}
	return hasChanges;
}

MenuReaction MenuString::engage() {
	hasChanges = true;
	if (isOpen) {
		index++;
		if (index>string.length() || (maxLength?index>maxLength:false)) {
			string.trim();
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
			string.trim();
			return MenuReaction::closeDown;
		}
		index--;
	}
	return MenuReaction::noReaction;
}

MenuReaction MenuString::increase() {
	if (index==string.length()) {
		string = string + ' ';
	}
	char newChar = string.charAt(index) + 1;
	if (newChar>126) {
		newChar = 32;
	}
	string.setCharAt(index, newChar);
	return MenuReaction::changeValue;
}

MenuReaction MenuString::decrease() {
	if (index==string.length()) {
		string = string + ' ';
	}
	char newChar = string.charAt(index) - 1;
	if (newChar<32) {
		newChar = 126;
	}
	string.setCharAt(index, newChar);
	return MenuReaction::changeValue;
}
