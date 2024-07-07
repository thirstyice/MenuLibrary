#pragma once

#include "MenuItem.h"

class MenuToggle : public MenuItem {
public:
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