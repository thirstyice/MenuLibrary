#pragma once

#include "MenuItem.h"

/**
** @brief Defines a Menu item for exiting a submenu
**
**/
class MenuBack : public MenuItem {
public:
	MenuBack(const char * _title) : MenuItem(_title) {}
	MenuBack() : MenuBack("Back") {}
protected:
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
private:
	MenuReaction engage() override {return MenuReaction::closeDown;}
};

extern MenuBack MenuBackDefault;