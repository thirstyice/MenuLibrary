#include "MenuBase.h"

MenuReaction MenuBase::distributeAction(MenuAction action) {
	MenuReaction returnValue = MenuReaction::noReaction;
	switch (action) {
	case MenuAction::engage:
		returnValue = engage();
		break;
	case MenuAction::disengage:
		returnValue = disengage();
		break;
	case MenuAction::increase:
		returnValue = increase();
		break;
	case MenuAction::decrease:
		returnValue = decrease();
		break;
	case MenuAction::getFocus:
		returnValue = getFocus();
		break;
	case MenuAction::loseFocus:
		returnValue = loseFocus();
		break;
	default:
		return MenuReaction::noReaction;
		break;
	}
	return returnValue;
}
MenuReaction MenuBase::doAction(MenuAction action) {
	return distributeAction(action); 
}

MenuBase* MenuBase::setResponder(void (*responder)(const MenuBase*), MenuEvent event) {
	responders[event].responder = responder;
	return this;
}

String MenuBase::getTitle() {
	hasChanges = false;
	return title;
}

MenuBase* MenuBase::setTitle(String _title) {
	title = _title;
	hasChanges = true;
}
