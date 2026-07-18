#pragma once

#include "MenuBase.h"

/**
** @brief Defines a Menu item which allows toggling a boolean variable
**
**/
class MenuToggle : public MenuBase<MenuToggle> {
public:
	/**
	** @brief MenuToggle constructor
	** @param _title The text to show before the editable value
	** @param var The variable to be controlled by the toggle
	** @param trueStr The text to display when the variable is true
	** @param falseStr The text to display when the variable is false
	**/
	MenuToggle(const char * _title, bool& var, const char * trueStr="True", const char * falseStr="False") :
		MenuBase(_title), variable(&var), trueLabel(trueStr), falseLabel(falseStr)
	{}
	bool needsRedraw() override;
	/**
	** @brief Change the variable being controlled by the toggle
	**
	** @param _variable
	** @return ** MenuToggle& Allows method chaining
	**/
	MenuToggle& setVar(bool& _variable);
	/**
	** @brief Set the text to be displayed when the variable is true
	**
	** @param label
	** @return ** MenuToggle& Allows method chaining
	**/
	MenuToggle& setTrue(const char * label);
	/**
	** @brief Set the text to be displayed when the variable is false
	**
	** @param label
	** @return ** MenuToggle& Allows method chaining
	**/
	MenuToggle& setFalse(const char * label);
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
private:
	MenuReaction engage() override;
	bool* variable;
	bool lastValue;
	const char * trueLabel;
	const char * falseLabel;
};