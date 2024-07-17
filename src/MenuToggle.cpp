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

String MenuToggle::getTitle() {
	hasChanges = false;
	lastValue = *variable;
	return (title + MenuChar[MenuChars::AlignRightFollowing] + (*variable?trueLabel:falseLabel));
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