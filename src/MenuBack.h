#pragma once

#include "MenuItem.h"

class MenuBack : public MenuItem {
public:
	MenuBack() : MenuItem("Back") {}
protected:
	String getTitle() override;
private:
	String title = "Back";
	MenuReaction engage() override {return MenuReaction::closeDown;}
};

extern MenuBack MenuBackDefault;