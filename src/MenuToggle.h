#pragma once

#include "MenuOp.h"

class MenuToggle final : public MenuOp {
public:
	MenuToggle() {};
	MenuToggle(String _title, bool* _variable, String _trueLabel = "true", String _falseLabel = "false");
	void setVariable(bool* _variable);
	void setTrueLabel(String _trueLabel);
	void setFalseLabel(String _falseLabel);
	String getTitle();
private:
	MenuEvent::Event handleClick();
	bool* variable = nullptr;
	bool lastValue;
	String trueLabel = "true";
	String falseLabel = "false";
};