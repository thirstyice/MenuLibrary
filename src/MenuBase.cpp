/*******************************************************************************
* Project: MenuLibrary                                                         *
* Filename: /src/MenuBase.cpp                                                  *
*                                                                              *
* Created: 2025-01-20                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2025 Tauran - https://github.com/thirstyice                    *
* For details see MenuLibrary/LICENSE (if applicable)                          *
*                                                                              *
*******************************************************************************/

#include "MenuBase.h"

MenuReaction MenuBase::doAction(MenuAction action) {
	return distributeAction(action);
}

void MenuBase::setResponder(void (*newResponder)(MenuEvent)) {
	responder.respond = newResponder;
}

void MenuBase::insertAfter(MenuCore* element) {
	setPrevious(element);
	setNext(element->getNext());
	element->getNext()->setPrevious((MenuCore*)this);
	element->setNext((MenuCore*)this);
}

void MenuBase::insertBefore(MenuCore* element) {
	element->getPrevious()->setNext((MenuCore*)this);
	element->setPrevious((MenuCore*)this);
}

void MenuBase::removeFromMenu() {
	next->setPrevious(previous);
	previous->setNext(next);
}

MenuReaction MenuBase::distributeAction(MenuAction action) {
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
	case MenuAction::gainFocus:
		reaction = getFocus();
		break;
	case MenuAction::loseFocus:
		reaction = loseFocus();
		break;
	default:
		return MenuReaction::noReaction;
		break;
	}
	responder.respond((MenuEvent)action);
	responder.respond((MenuEvent)reaction);
	return reaction;
}