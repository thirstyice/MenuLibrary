#pragma once

#include "MenuBase.h"

class MenuItem : public MenuBase<MenuItem> {
public:
	using MenuBase<MenuItem>::MenuBase;
};