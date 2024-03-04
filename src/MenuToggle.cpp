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

bool MenuToggle::handleClick() {
	if (variable != nullptr) {
		*variable = !*variable;
	}
	return false;
}

String MenuToggle::getTitle() {
	return (title + "\t" + (*variable?trueLabel:falseLabel));
}

void MenuToggle::setVariable(bool* _variable) {
	variable = _variable;
}

void MenuToggle::setTrueLabel(String _trueLabel) {
	trueLabel = _trueLabel;
}

void MenuToggle::setFalseLabel(String _falseLabel) {
	falseLabel = _falseLabel;
}