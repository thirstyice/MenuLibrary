#pragma once

#include "MenuOp.h"

class MenuBack : public MenuOp {
protected:
	String title = "<- Back";
private:
	Event handleClick() {return exit;}
};