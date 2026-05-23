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

MenuCore::TitleFlags MenuValue::getTitle(char* buf, const uint8_t& len) {
	TitleFlags flags;
	const char* titleChar = &title[strlen(title)-1];

	hasChanges = false;

	uint8_t valueStrSize[size];
	uint16_t valueStrTotal = 0;
	for (uint8_t i=0; i<size; i++) {
		valueStrSize[i] = strlen(values[i]->getValueAsString().c_str());
		valueStrTotal += valueStrSize[i];
	}
	uint8_t beginAtValue = 0;
	if (valueStrTotal >= (len-1)-strlen(title) && isOpen) {
		strcpy(buf, &title[strlen(title)-1]);
		if (valueStrTotal >= len-1) {
			uint8_t testChars = valueStrSize[selected];
			beginAtValue = selected;
			// TODO incorporate c strings
		}
	} else {
		strlcpy(buf, title, len);
	}

	flags.alignRightFrom = strlen(buf);
	while (strlcat(buf, values[beginAtValue]->getValueAsString().c_str(), len) < len) {
		beginAtValue++;
		if (beginAtValue>=size) {
			break;
		}
		char sep[] = {separator, '\0'};
		strlcat(buf, sep, len);
		if (beginAtValue==selected) {
			flags.selectionStart = strlen(buf);
		}
	}
	if (isOpen) {
		flags.selectionLength = strlen(values[selected]->getValueAsString().c_str());
	}



	} else {
		strlcpy(buf, title, len);
		flags.alignRightFrom = strlen(buf);
		uint8_t i=0;
		while (strlcat(buf, values[i]->getValueAsString().c_str(), len) < len) {
			i++;
			if (i>=size) {
				break;
			}
			char sep[] = {separator, '\0'};
			strlcat(buf, sep, len);
		}
	}

	String valuesString = "";
	for (uint8_t i=0; i<size; i++) {
		String variableString = values[i]->getValueAsString();
		if (isOpen == true && selected == i) {
			variableString = String(MenuChar[MenuChars::StartOfSelection]) + variableString + String(MenuChar[MenuChars::EndOfSelection]);
		}
		valuesString += variableString + MenuChar[MenuChars::Break] + separator + String(MenuChar[MenuChars::ReplaceableWithCursor]);
	}
	valuesString.remove(valuesString.length()-3); // The trailing separator
	return (title + MenuChar[MenuChars::Break] + MenuChar[MenuChars::AlignRightFollowing] + valuesString);
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

MenuValue::MenuValue(const MenuValue &og) : MenuBase(og.title) {
	separator = og.separator;
	size = og.size;
	size_t memsize = size * sizeof(MenuValuesOp*);
	values = (MenuValuesOp**)malloc(memsize);
	memcpy(values, og.values, memsize);
}

MenuValue::~MenuValue() {
	for (uint8_t i=0; i<size; i++) {
		delete values[i];
	}
	free(values);
}