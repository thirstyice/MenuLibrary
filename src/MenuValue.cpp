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

TitleFlags MenuValue::getTitle(char* buf, const uint8_t& len) {
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
		strcpy(buf, titleChar);
		if (valueStrTotal >= (uint16_t)(len-1)) {
			uint8_t testChars = valueStrSize[selected];
			beginAtValue = selected;
			uint8_t loop = 1;
			while (testChars < len-1) {
				if (selected + loop < size) {
					testChars += valueStrSize[selected + loop] + 1;
				}
				if (selected - loop >= 0) {
					testChars += valueStrSize[selected - loop] + 1;
					beginAtValue = selected - loop;
				}
			}
		}
	} else {
		strlcpy(buf, title, len);
	}

	flags.alignRightFrom = strlen(buf);
	flags.selectionStart = strlen(buf);
	char sep[] = {separator, '\0'};
	while (strlcat(buf, values[beginAtValue]->getValueAsString().c_str(), len) < len) {
		beginAtValue++;
		if (beginAtValue>=size) {
			break;
		}
		strlcat(buf, sep, len);
		if (beginAtValue==selected) {
			flags.selectionStart = strlen(buf);
			flags.replaceableWithCursor[0] = strlen(buf);
		}
	}
	if (isOpen) {
		flags.selectionLength = valueStrSize[selected];
	}
	return flags;
}

MenuValue& MenuValue::setSeparator(char _separator) {
	separator = _separator;
	hasChanges = true;
	return *this;
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