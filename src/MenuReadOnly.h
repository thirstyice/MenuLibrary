/*******************************************************************************
* Project: MenuLibrary                                                         *
* Filename: /src/MenuReadOnly.h                                                *
*                                                                              *
* Created: 2026-03-23                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see MenuLibrary/LICENSE (if applicable)                          *
*                                                                              *
*******************************************************************************/
#pragma once

#include "MenuBase.h"

class MenuReadOnly : public MenuBase<MenuReadOnly> {
public:
	MenuReadOnly(String _title, MenuCore& _var) : MenuBase(_title), var(&_var) {}
	MenuReadOnly(String _title, MenuCore* _var) : MenuBase(_title), var(_var) {}
	String getTitle() override {
		return title + var->getTitle();
	}
	bool needsRedraw() {
		return var->needsRedraw();
	}
protected:
	MenuCore* var;
private:
}; // class MenuReadOnly