#include "MenuToggle.h"

MenuToggle::MenuToggle(
	String _title,
	bool* _variable,
	String _trueLabel,
	String _falseLabel) 
	: 
	variable(_variable),
	trueLabel(_trueLabel),
	falseLabel(_falseLabel) 
{
	title = _title;
}

bool MenuToggle::needsRedraw() {
	return (*variable != lastValue) || hasChanged;
}

MenuEvent::Event MenuToggle::handleClick() {
	if (variable != nullptr) {
		*variable = !*variable;
	}
	return MenuEvent::noEvent;
}

String MenuToggle::getTitle() {
	hasChanged = false;
	lastValue = *variable;
	return (title + MenuChar[MenuChars::AlignRightFollowing] + (*variable?trueLabel:falseLabel));
}

void MenuToggle::setVariable(bool* _variable) {
	variable = _variable;
}

void MenuToggle::setTrueLabel(String _trueLabel) {
	trueLabel = _trueLabel;
	if (*variable == true) {
		hasChanged = true;
	}
}

void MenuToggle::setFalseLabel(String _falseLabel) {
	falseLabel = _falseLabel;
	if (*variable == false) {
		hasChanged = true;
	}
}