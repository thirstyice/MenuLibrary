#pragma once

#include "MenuBase.h"

class MenuItem : public MenuBase<MenuItem> {
public:
	MenuItem(String _title) : MenuBase(_title) {}
};