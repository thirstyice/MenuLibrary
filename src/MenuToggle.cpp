#include "MenuToggle.h"

bool MenuToggle::needsRedraw() {
	return (*variable != lastValue) || hasChanges;
}

MenuReaction MenuToggle::engage() {
	if (variable != nullptr) {
		*variable = !*variable;
		return MenuReaction::changeValue;
	}
	return MenuReaction::noReaction;
}

MenuCore::TitleFlags MenuToggle::getTitle(char* buf, const uint8_t& len) {
	TitleFlags flags;
	hasChanges = false;
	lastValue = variable;
	strlcpy(buf, title, len);
	flags.alignRightFrom = strlen(buf);
	strlcat(buf, (variable?trueLabel:falseLabel), len);
	return flags;
}

MenuToggle* MenuToggle::setVar(bool* var) {
	variable = var;
	return this;
}

MenuToggle* MenuToggle::setTrue(String label) {
	trueLabel = label;
	if (*variable == true) {
		hasChanges = true;
	}
	return this;
}

MenuToggle* MenuToggle::setFalse(String label) {
	falseLabel = label;
	if (*variable == false) {
		hasChanges = true;
	}
	return this;
}