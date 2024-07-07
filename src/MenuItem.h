#pragma once

#include "MenuOutput/MenuOutput.h"

typedef uint8_t MenuEvent;

enum struct MenuAction : MenuEvent {
	noAction = 0,
	engage,
	disengage,
	increase,
	decrease,
	getFocus,
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

struct MenuResponder {
	static void doNothing(const MenuItem*) {return;}
	void (*responder)(const MenuItem*) = doNothing;
};

class MenuItem {
public:
	MenuItem* setResponder(void (*responder)(const MenuItem*), MenuEvent event);
	MenuItem* setTitle(String _title);
	virtual String getTitle();
	virtual bool doDraw() {return false;}
	virtual MenuItem* setOutput(MenuOutput** outputArray, uint8_t outputCount) {}
	virtual MenuReaction doAction(MenuAction action);
	virtual ~MenuItem() {}

private:
	static const uint8_t numEvents = (uint8_t)MenuReaction::lastReaction;
	MenuReaction distributeAction(MenuAction action);
	virtual MenuItem* setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) {};
	virtual MenuReaction engage() {return MenuReaction::noReaction;}
	virtual MenuReaction disengage() {return MenuReaction::closeDown;}
	virtual MenuReaction increase() {return MenuReaction::noReaction;}
	virtual MenuReaction decrease() {return MenuReaction::noReaction;}
	virtual MenuReaction getFocus() {return MenuReaction::noReaction;}
	virtual MenuReaction loseFocus() {return MenuReaction::noReaction;}
	virtual void handleReaction(MenuReaction) {}

protected:
	virtual bool needsRedraw() {return hasChanges;}
	String title = "-";
	MenuResponder responders[numEvents];
	//bool hasFocus = false;
	bool isOpen = false;
	bool hasChanges = true;
};