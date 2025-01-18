#pragma once

#include "MenuOutput/MenuOutput.h"

typedef uint8_t MenuEvent;

enum struct MenuAction : MenuEvent {
	noAction = 0,
	engage,
	disengage,
	increase,
	decrease,
	gainFocus,
	loseFocus,
	lastAction
};
enum struct MenuReaction : MenuEvent {
	noReaction = (MenuEvent)MenuAction::lastAction + 1,
	openUp,
	closeDown,
	changeValue,
	lastReaction
};


class MenuCore {
public:
	MenuCore() : title("-") {};
	MenuCore(const char* _title) : title(_title) {}
	virtual String getTitle() {hasChanges = false; return title;};
	virtual bool doDraw() {return false;}
	virtual MenuReaction doAction(MenuAction action) =0;
	virtual ~MenuCore() {}
	virtual void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) {};
	virtual bool needsRedraw() {return hasChanges;}
	MenuCore* getNext() {return next;}
	MenuCore* getPrevious() {return previous;}
	void setPrevious(MenuCore* element) {previous=element;}
	void setNext(MenuCore* element) {next=element;}
protected:

	static const uint8_t numEvents = (uint8_t)MenuReaction::lastReaction;
	virtual MenuReaction engage() {return MenuReaction::noReaction;}
	virtual MenuReaction disengage() {return MenuReaction::closeDown;}
	virtual MenuReaction increase() {return MenuReaction::noReaction;}
	virtual MenuReaction decrease() {return MenuReaction::noReaction;}
	virtual MenuReaction getFocus() {return MenuReaction::noReaction;}
	virtual MenuReaction loseFocus() {return MenuReaction::noReaction;}
	const char* title;
	bool isOpen = false;
	bool hasChanges = true;
	MenuCore* previous = nullptr;
	MenuCore* next = nullptr;
};

template <class MenuDerived>
class MenuBase : public MenuCore {
public:
	using MenuCore::MenuCore;
	MenuBase(const char* title, MenuCore* after) : MenuCore(title) {if (after) {insertAfter(after);}}
	MenuDerived* setResponder(void (*responder)(MenuDerived*), MenuAction action);
	MenuDerived* setResponder(void (*responder)(MenuDerived*), MenuReaction reaction);
	MenuDerived* insertAfter(MenuCore* element);
	MenuDerived* insertBefore(MenuCore* element);
	MenuDerived* removeFromMenu();
	virtual MenuReaction doAction(MenuAction action) override;

protected:
	MenuReaction distributeAction(MenuAction action);
private:
	/**
	** @brief Defines handlers for MenuEvents
	** Handlers are called after the item deals with the Event internally
	** Action handlers are called first, by the item being acted upon
	** Reactions are called second, by the object that is reacting
	**/
	struct MenuResponder {
		static void doNothing(MenuDerived*) {return;}
		void (*responder)(MenuDerived*) = doNothing;
	};
	MenuResponder responders[numEvents];
};

template <class MenuDerived>
MenuReaction MenuBase<MenuDerived>::doAction(MenuAction action) {
	return distributeAction(action);
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::setResponder(void (*responder)(MenuDerived*), MenuAction event) {
	responders[(MenuEvent)event].responder = responder;
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::setResponder(void (*responder)(MenuDerived*), MenuReaction event) {
	responders[(MenuEvent)event].responder = responder;
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::insertAfter(MenuCore* element) {
	setPrevious(element);
	setNext(element->getNext());
	element->getNext()->setPrevious((MenuCore*)this);
	element->setNext((MenuCore*)this);
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::insertBefore(MenuCore* element) {
	element->getPrevious()->setNext((MenuCore*)this);
	element->setPrevious((MenuCore*)this);
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::removeFromMenu() {
	next->setPrevious(previous);
	previous->setNext(next);
	return (MenuDerived*)this;
}

template <class MenuDerived>
MenuReaction MenuBase<MenuDerived>::distributeAction(MenuAction action) {
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
	responders[(MenuEvent)action].responder((MenuDerived*)this);
	responders[(MenuEvent)reaction].responder((MenuDerived*)this);
	return reaction;
}