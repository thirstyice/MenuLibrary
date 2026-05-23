#pragma once

#include "MenuBase.h"

class MenuItem : public MenuBase<MenuItem> {
public:
	MenuItem(const char* _title) : MenuBase(_title) {}
};