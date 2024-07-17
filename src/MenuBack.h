#pragma once

#include "MenuItem.h"

class MenuBack : public MenuItem {
public:
	MenuBack(String _title) : MenuItem(_title) {}
	MenuBack() : MenuBack("Back") {}
protected:
	String getTitle() override;
private:
	MenuReaction engage() override {return MenuReaction::closeDown;}
};

extern MenuBack MenuBackDefault;