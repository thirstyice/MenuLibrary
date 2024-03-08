#pragma once

#include "MenuOp.h"

class MenuBackClass : public MenuOp {
public:
	MenuBackClass(String _title = "Back") {title = _title;}
protected:
	String getTitle();
private:
	MenuEvent::Event handleClick() {return MenuEvent::back;}
};

extern MenuBackClass MenuBack;