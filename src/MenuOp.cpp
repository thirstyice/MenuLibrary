#include "MenuOp.h"

MenuEvent::Event MenuOp::passEventToHandlerFunctions(MenuEvent::Event event) {
	MenuEvent::Event returnValue = MenuEvent::noEvent;
	switch (event) {
	case MenuEvent::click:
		returnValue = handleClick();
		break;
	case MenuEvent::back:
		returnValue = handleBack();
		break;
	case MenuEvent::focus:
		returnValue = handleFocus();
		break;
	case MenuEvent::unfocus:
		returnValue = handleUnfocus();
		break;
	case MenuEvent::enter:
		returnValue = handleEnter();
		break;
	case MenuEvent::exit:
		returnValue = handleExit();
		break;
	case MenuEvent::scrollNext:
		returnValue = handleScrollNext();
		break;
	case MenuEvent::scrollPrevious:
		returnValue = handleScrollPrevious();
		break;
	default:
		return MenuEvent::noEvent;
		break;
	}
	handlers[event].handler(this);
	return returnValue;
}
MenuEvent::Event MenuOp::handleEvent(MenuEvent::Event event) {
	if (event == MenuEvent::focus) {
		hasFocus = true;
	}
	if (event == MenuEvent::unfocus) {
		hasFocus = false;
	}
	return passEventToHandlerFunctions(event); 
}

void MenuOp::setHandlerForEvent(void (*handler)(const MenuOp*), MenuEvent::Event event) {
	handlers[event].handler = handler;
}

String MenuOp::getTitle() {
	hasChanged = false;
	return title;
}

void MenuOp::setTitle(String _title) {
	title = _title;
	hasChanged = true;
}
