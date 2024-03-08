#pragma once

#include "MenuOutput/MenuOutput.h"

struct MenuEvent { enum Event : uint8_t {
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
};};

class MenuOp {
public:
	static void doNothing(const MenuOp*) {return;}
	void setHandlerForEvent(void (*handler)(const MenuOp*), MenuEvent::Event event);
	void setTitle(String _title);
	virtual String getTitle();
	virtual bool draw() {return false;}
	virtual void setOutput(MenuOutput* outputArray, uint8_t outputCount) {}
	virtual MenuEvent::Event handleEvent(MenuEvent::Event event);
	virtual ~MenuOp() {}


protected:
	MenuEvent::Event passEventToHandlerFunctions(MenuEvent::Event event);
	String title = "-";
	struct {		
		void (*handler)(const MenuOp*) = doNothing;
	} handlers[MenuEvent::lastEvent];
	bool hasFocus = false;
	bool active = false;
private:
	virtual MenuEvent::Event handleClick() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleBack() {return MenuEvent::exit;}
	virtual MenuEvent::Event handleFocus() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleEnter() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleUnfocus() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleExit() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleScrollNext() {return MenuEvent::noEvent;}
	virtual MenuEvent::Event handleScrollPrevious() {return MenuEvent::noEvent;}
};