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

class MenuBase : public MenuCore {
public:
	using MenuCore::MenuCore;
	MenuBase(const char* title, MenuCore* after) : MenuCore(title) {if (after) {insertAfter(after);}}
	void setResponder(void (*responder)(MenuEvent));
	void insertAfter(MenuCore* element);
	void insertBefore(MenuCore* element);
	void removeFromMenu();
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
		static void doNothing(MenuEvent) {return;}
		void (*respond)(MenuEvent) = doNothing;
	};
	MenuResponder responder;
};