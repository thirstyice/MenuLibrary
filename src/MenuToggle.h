#pragma once

#include "MenuBase.h"

class MenuToggle : public MenuBase<MenuToggle> {
public:
	MenuToggle(String _title) : MenuBase(_title) {}
	MenuToggle(String _title, bool* var) : MenuBase(_title), variable(var) {}
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