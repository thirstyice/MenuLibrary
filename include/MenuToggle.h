#pragma once

#include "MenuOp.h"

class MenuToggle : public MenuOp {
public:
	MenuToggle() {};
	MenuToggle(String _title, bool* _variable, String _trueLabel = "true", String _falseLabel = "false");
	void setVariable(bool* _variable);
	void setTrueLabel(String _trueLabel);
	void setFalseLabel(String _falseLabel);
	String getTitle() const;
private:
	virtual MenuEvent::Event handleClick();
	bool* variable = nullptr;
	String trueLabel = "true";
	String falseLabel = "false";
};