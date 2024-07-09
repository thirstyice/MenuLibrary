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
	MenuCore() {};
	MenuCore(String _title) : title(_title) {}
	virtual String getTitle() {hasChanges = false; return title;};
	virtual bool doDraw() {return false;}
	virtual MenuReaction doAction(MenuAction action) =0;
	virtual ~MenuCore() {}
	virtual void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) {};
	virtual bool needsRedraw() {return hasChanges;}

protected:

	static const uint8_t numEvents = (uint8_t)MenuReaction::lastReaction;
	virtual MenuReaction engage() {return MenuReaction::noReaction;}
	virtual MenuReaction disengage() {return MenuReaction::closeDown;}
	virtual MenuReaction increase() {return MenuReaction::noReaction;}
	virtual MenuReaction decrease() {return MenuReaction::noReaction;}
	virtual MenuReaction getFocus() {return MenuReaction::noReaction;}
	virtual MenuReaction loseFocus() {return MenuReaction::noReaction;}
	String title = "-";
	bool isOpen = false;
	bool hasChanges = true;
};

template <class MenuDerived>
class MenuBase : public MenuCore {
public:
	MenuBase(String _title) : MenuCore(_title) {};
	MenuDerived* setResponder(void (*responder)(const MenuDerived*), MenuAction action);
	MenuDerived* setResponder(void (*responder)(const MenuDerived*), MenuReaction reaction);
	MenuDerived* setTitle(String _title);
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
		static void doNothing(const MenuDerived*) {return;}
		void (*responder)(const MenuDerived*) = doNothing;
	};
	MenuResponder responders[numEvents];
};

template <class MenuDerived>
MenuReaction MenuBase<MenuDerived>::doAction(MenuAction action) {
	return distributeAction(action);
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::setResponder(void (*responder)(const MenuDerived*), MenuAction event) {
	responders[(MenuEvent)event].responder = responder;
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::setResponder(void (*responder)(const MenuDerived*), MenuReaction event) {
	responders[(MenuEvent)event].responder = responder;
	return (MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived* MenuBase<MenuDerived>::setTitle(String _title) {
	title = _title;
	hasChanges = true;
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
	responders[(MenuEvent)action].responder(this);
	responders[(MenuEvent)reaction].responder(this);
	return reaction;
}