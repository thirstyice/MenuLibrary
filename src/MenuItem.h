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

class MenuItem {
public:
	MenuItem* setResponder(void (*responder)(const MenuItem*), MenuAction action);
	MenuItem* setResponder(void (*responder)(const MenuItem*), MenuReaction reaction);
	MenuItem* setTitle(String _title);
	virtual String getTitle();
	virtual bool doDraw() {return false;}
	virtual MenuReaction doAction(MenuAction action);
	virtual ~MenuItem() {}

	virtual void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) {};
	virtual bool needsRedraw() {return hasChanges;}

private:
	static const uint8_t numEvents = (uint8_t)MenuReaction::lastReaction;
	virtual MenuReaction engage() {return MenuReaction::noReaction;}
	virtual MenuReaction disengage() {return MenuReaction::closeDown;}
	virtual MenuReaction increase() {return MenuReaction::noReaction;}
	virtual MenuReaction decrease() {return MenuReaction::noReaction;}
	virtual MenuReaction getFocus() {return MenuReaction::noReaction;}
	virtual MenuReaction loseFocus() {return MenuReaction::noReaction;}

	/**
	** @brief Defines handlers for MenuEvents
	** Handlers are called after the item deals with the Event internally
	** Action handlers are called first, by the item being acted upon
	** Reactions are called second, by the object that is reacting
	**/
	struct MenuResponder {
		static void doNothing(const MenuItem*) {return;}
		void (*responder)(const MenuItem*) = doNothing;
	};

protected:
	MenuReaction distributeAction(MenuAction action);
	String title = "-";
	MenuResponder responders[numEvents];
	//bool hasFocus = false;
	bool isOpen = false;
	bool hasChanges = true;
};