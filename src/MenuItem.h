#pragma once

#include <Arduino.h>

#include <MenuOp.h>

class MenuItem : public MenuOp {
public:
	MenuItem() {}
	MenuItem(String _title) {title = _title;}
};

