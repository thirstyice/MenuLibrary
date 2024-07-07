#include "MenuItem.h"

MenuReaction MenuItem::distributeAction(MenuAction action) {
	MenuReaction reaction = MenuReaction::noReaction;
	switch (action) {
	case MenuAction::engage:
		reaction = engage();
		break;
	case MenuAction::disengage:
		reaction = disengage();
		break;
	case MenuAction::increase:
		reaction = increase();
		break;
	case MenuAction::decrease:
		reaction = decrease();
		break;
	case MenuAction::getFocus:
		reaction = getFocus();
		break;
	case MenuAction::loseFocus:
		reaction = loseFocus();
		break;
	default:
		return MenuReaction::noReaction;
		break;
	}
	responders[(MenuEvent)action].responder(this);
	responders[(MenuEvent)reaction].responder(this);
	return reaction;
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
