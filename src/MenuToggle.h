#pragma once

#include "MenuBase.h"

class MenuToggle : public MenuBase<MenuToggle> {
public:
	MenuToggle(const char* _title, MenuCore* after, bool* var, const char* trueStr="True", const char* falseStr="False") :
		MenuBase(_title, after), variable(var), trueLabel(trueStr), falseLabel(falseStr)
	{}
	bool needsRedraw() override;
	MenuToggle* setVar(bool* _variable);
	String getTitle() override;
private:
	MenuReaction engage() override;
	bool* variable = nullptr;
	bool lastValue;
	const char* trueLabel;
	const char* falseLabel;
};