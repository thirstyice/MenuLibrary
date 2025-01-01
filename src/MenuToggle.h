#pragma once

#include "MenuBase.h"

class MenuToggle : public MenuBase<MenuToggle> {
public:
	MenuToggle(String _title, bool* var, MenuCore* after = nullptr, String trueStr="True", String falseStr="False") :
		MenuBase(_title, after), variable(var), trueLabel(trueStr), falseLabel(falseStr)
	{}
	bool needsRedraw() override;
	MenuToggle* setVar(bool* _variable);
	MenuToggle* setTrue(String label);
	MenuToggle* setFalse(String label);
	String getTitle() override;
private:
	MenuReaction engage() override;
	bool* variable = nullptr;
	bool lastValue;
	String trueLabel = "true";
	String falseLabel = "false";
};