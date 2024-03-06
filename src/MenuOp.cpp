#include "MenuOp.h"

MenuOp::Event MenuOp::passEventToHandlerFunctions(Event event) {
	Event returnValue = noEvent;
	switch (event) {
	case click:
		returnValue = handleClick();
		break;
	case back:
		returnValue = handleBack();
		break;
	case focus:
		returnValue = handleFocus();
		break;
	case unfocus:
		returnValue = handleUnfocus();
		break;
	case enter:
		returnValue = handleEnter();
		break;
	case exit:
		returnValue = handleExit();
		break;
	case scrollNext:
		returnValue = handleScrollNext();
		break;
	case scrollPrevious:
		returnValue = handleScrollPrevious();
		break;
	default:
		return noEvent;
		break;
	}
	handlers[event].handler(this);
	return returnValue;
}
MenuOp::Event MenuOp::handleEvent(Event event) {
	if (event == focus) {
		hasFocus = true;
	}
	if (event == unfocus) {
		hasFocus = false;
	}
	return passEventToHandlerFunctions(event); 
}

void MenuOp::setHandlerForEvent(void (*handler)(const MenuOp*), Event event) {
	handlers[event].handler = handler;
}

String MenuOp::getTitle() {
	return title;
}

void MenuOp::setTitle(String _title) {
	title = _title;
}
