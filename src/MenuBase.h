#pragma once

#include "MenuOutput/MenuOutput.h"

typedef uint8_t MenuEvent;

enum MenuAction : MenuEvent {
	noAction = 0,
	engage,
	disengage,
	increase,
	decrease,
	gainFocus,
	loseFocus,
	lastAction
};
enum MenuReaction : MenuEvent {
	noReaction = (MenuEvent)MenuAction::lastAction + 1,
	openUp,
	closeDown,
	changeValue,
	lastReaction
};


class MenuCore {
public:
	MenuCore() {};
	MenuCore(const char * _title) : title(_title) {}

	struct TitleFlags { // Indexes in title for formatting
		uint8_t selectionStart = 0; // First character in selection
		uint8_t selectionLength = 0; // Length of selection
		uint8_t alignRightFrom = 255; // First character to be aligned right
		uint8_t replaceableWithCursor[3] = {255, 255, 255};
	};


	virtual TitleFlags getTitle(char* buf, const uint8_t& len) {
		hasChanges = false;
		strlcpy(buf, title, len);
	};
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
	const char * title;
	bool isOpen = false;
	bool hasChanges = true;
};

template <class MenuDerived>
class MenuBase : public MenuCore {
public:
	MenuBase(const char * _title) : MenuCore(_title) {};
	MenuDerived& setResponder(void (*responder)(MenuDerived*), MenuEvent action);
	MenuDerived& setTitle(const char * _title);
	virtual MenuReaction doAction(MenuAction action) override;

protected:
	MenuReaction distributeAction(MenuAction& action);
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
MenuDerived& MenuBase<MenuDerived>::setResponder(void (*responder)(MenuDerived*), MenuEvent event) {
	responders[(MenuEvent)event].responder = responder;
	return *(MenuDerived*)this;
}
template <class MenuDerived>
MenuDerived& MenuBase<MenuDerived>::setTitle(const char* _title) {
	title = _title;
	hasChanges = true;
	return *(MenuDerived*)this;
}

template <class MenuDerived>
MenuReaction MenuBase<MenuDerived>::distributeAction(MenuAction& action) {
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
	responders[action].responder((MenuDerived*)this);
	responders[reaction].responder((MenuDerived*)this);
	return reaction;
}