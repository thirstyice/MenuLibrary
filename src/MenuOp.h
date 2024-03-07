#pragma once

#include "MenuOutput/MenuOutput.h"

class MenuOp {
public:
	enum Event : uint8_t {
		noEvent = 0,
		click,
		back,
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
	virtual Event handleEvent(Event event);
	virtual ~MenuOp() {}


protected:
	Event passEventToHandlerFunctions(Event event);
	String title = "-";
	struct {		
		void (*handler)(const MenuOp*) = doNothing;
	} handlers[lastEvent];
	bool hasFocus = false;
	bool active = false;
private:
	virtual Event handleClick() {return noEvent;}
	virtual Event handleBack() {return exit;}
	virtual Event handleFocus() {return noEvent;}
	virtual Event handleEnter() {return noEvent;}
	virtual Event handleUnfocus() {return noEvent;}
	virtual Event handleExit() {return noEvent;}
	virtual Event handleScrollNext() {return noEvent;}
	virtual Event handleScrollPrevious() {return noEvent;}
};