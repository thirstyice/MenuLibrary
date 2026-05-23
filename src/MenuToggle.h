#pragma once

#include "MenuBase.h"

class MenuToggle : public MenuBase<MenuToggle> {
public:
	MenuToggle(const char * _title, bool& var, const char * trueStr="True", const char * falseStr="False") :
		MenuBase(_title), variable(var), trueLabel(trueStr), falseLabel(falseStr)
	{}
	bool needsRedraw() override;
	MenuToggle& setVar(bool& _variable);
	MenuToggle& setTrue(const char * label);
	MenuToggle& setFalse(const char * label);
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
private:
	MenuReaction engage() override;
	bool& variable;
	bool lastValue;
	const char * trueLabel;
	const char * falseLabel;
};