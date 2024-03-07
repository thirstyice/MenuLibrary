#pragma once

#include "MenuOp.h"

class MenuBackClass : public MenuOp {
public:
	MenuBackClass(String _title = "<- Back") {title = _title;}
private:
	Event handleClick() {return exit;}
};

extern MenuBackClass MenuBack;