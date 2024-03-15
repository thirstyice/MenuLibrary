#pragma once

#include "MenuOp.h"

class MenuItem final : public MenuOp {
public:
	MenuItem() {}
	MenuItem(String _title) {title = _title;}
};

