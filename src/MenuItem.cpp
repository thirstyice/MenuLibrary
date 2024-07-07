#include "MenuItem.h"

MenuReaction MenuItem::distributeAction(MenuAction action) {
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
MenuReaction MenuItem::doAction(MenuAction action) {
	return distributeAction(action); 
}

MenuItem* MenuItem::setResponder(void (*responder)(const MenuItem*), MenuEvent event) {
	responders[event].responder = responder;
	return this;
}

String MenuItem::getTitle() {
	hasChanges = false;
	return title;
}

MenuItem* MenuItem::setTitle(String _title) {
	title = _title;
	hasChanges = true;
}
