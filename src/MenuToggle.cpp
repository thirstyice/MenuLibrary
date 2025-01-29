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
	return (_getTitle() + MenuChar[MenuChars::AlignRightFollowing] + (*variable?trueLabel:falseLabel));
}

MenuToggle* MenuToggle::setVar(bool* var) {
	variable = var;
	return this;
}
