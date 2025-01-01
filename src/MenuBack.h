#pragma once

#include "MenuItem.h"

class MenuBack : public MenuItem {
public:
	using MenuItem::MenuItem;
	MenuBack() : MenuBack("Back") {}
protected:
	String getTitle() override;
private:
	MenuReaction engage() override {return MenuReaction::closeDown;}
};