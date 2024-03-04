#pragma once

#include <Arduino.h>

#include "MenuOutput/MenuOutput.h"

class MenuOp {
public:
	enum Event : uint8_t {
		noEvent = 0,
		click,
		focus,
		unfocus,
		enter,
		exit,
		scrollNext,
		scrollPrevious,
		lastEvent
	};
	static void doNothing(const MenuOp*) {return;}
	void setHandlerForEvent(void (*handler)(const MenuOp*), Event event);
	void setTitle(String _title);
	virtual String getTitle();
	virtual bool draw() {return false;}
	virtual void setOutput(MenuOutput* outputArray, uint8_t outputCount) {}
	virtual bool handleEvent(Event event);
	virtual ~MenuOp() {}


protected:
	bool passEventToHandlerFunctions(Event event);
	void setParent(MenuOp* _parent) {parent = _parent;}
	String title = "-";
	struct {		
		void (*handler)(const MenuOp*) = doNothing;
	} handlers[lastEvent];
	bool hasFocus = false;
	MenuOp* parent = nullptr;
private:
	virtual bool handleClick() {return false;}
	virtual bool handleFocus() {return false;}
	virtual bool handleEnter() {return false;}
	virtual bool handleUnfocus() {return false;}
	virtual bool handleExit() {return false;}
	virtual bool handleScrollNext() {return false;}
	virtual bool handleScrollPrevious() {return false;}
};