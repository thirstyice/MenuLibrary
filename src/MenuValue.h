#pragma once

#include "MenuBase.h"

/**
** @brief Defines the common interface for the different types of values that
** can be included in a MenuValue
**
**/
class MenuValuesOp {
public:
	virtual String getValueAsString() =0;
	virtual void increment() =0;
	virtual void decrement() =0;
	virtual bool valueHasChanged() =0;
	virtual ~MenuValuesOp() {};
};

/**
** @brief Defines a single value for inclusion in a MenuValue object
**
** @tparam numberType
** The type of the value
**/
template <typename numberType>
class MenuValues : public MenuValuesOp {
private:
	numberType& variable;
	numberType lastValue;
	numberType max = 1;
	numberType min = 0;
	numberType inc = 1;
public:
	MenuValues() {}
	MenuValues(
		numberType& _variable,
		numberType _max = 1,
		numberType _min = 0,
		numberType _increment = 1
	) :
		variable{_variable},
		max{_max},
		min{_min},
		inc{_increment}
	{}
	/**
	** @brief Get a String representation of the value
	**
	** @return ** String
	**/
	String getValueAsString() override;
	/**
	** @brief Increment the value
	**
	** @return ** void
	**/
	void increment() override;
	/**
	** @brief Decrement the value
	**
	** @return ** void
	**/
	void decrement() override;
	/**
	** @brief Check if the value has changed
	**
	** @return true
	** @return false
	**/
	bool valueHasChanged() override;
	/**
	** @brief Set the Variable object that the value will track
	**
	** @param _variable The variable to track
	** @return ** MenuValues& Allows chaining methods
	**/
	MenuValues& setVariable(numberType* _variable) {variable = _variable; return *this;}
	/**
	** @brief Set the value beyond which the variable will not increment
	**
	** @param _max
	** @return ** MenuValues& Allows chaining methods
	**/
	MenuValues& setMax(numberType _max);
	/**
	** @brief Set the value below which the variable will not decrement
	**
	** @param _min
	** @return ** MenuValues& Allows chaining methods
	**/
	MenuValues& setMin(numberType _min);
	/**
	** @brief Set the amount by which the variable will be incremented / decremented
	**
	** @param _inc
	** @return ** MenuValues& Allows method chaining
	**/
	MenuValues& setIncrement(numberType _inc) {inc = _inc; return *this;}
};
/**
** @brief Defines a menu item that can alter the value of one or more variables,
** each of which is contained in a MenuValues object
**
**/
class MenuValue : public MenuBase<MenuValue> {
public:
	/**
	** @brief Create a MenuValue object using references
	**
	** @param _title The title to show before the editable values
	** @param arg1 The first editable value
	** @param args Subsequent editable values (up to 254)
	**/
	template <typename... Ts>
	MenuValue(const char * _title, MenuValuesOp& arg1, Ts... args);
	/**
	** @brief Create a MenuValue object using pointers
	**
	** @param _title The title to show before the editable values
	** @param arg1 A pointer to the first editable value
	** @param args Pointers to subsequent editable values (up to 254)
	**/
	template <typename... Ts>
	MenuValue(const char * _title, MenuValuesOp* arg1, Ts... args);
	MenuValue(const MenuValue &);
	~MenuValue();
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
	bool needsRedraw() override;
	/**
	** @brief Set the character to insert between editable values
	**
	** @param _separator
	** @return ** MenuValue& Allows method chaining
	**/
	MenuValue& setSeparator(char _separator);

private:
	char separator = ' ';
	uint8_t selected = 0;
	uint8_t size = 0;
	MenuReaction engage();
	MenuReaction disengage();
	MenuReaction increase();
	MenuReaction decrease();
	MenuValuesOp** values;
};

template <typename... Ts>
MenuValue::MenuValue(const char * _title, MenuValuesOp* arg1, Ts...args) : MenuBase(_title) {
	size = sizeof...(args)+1;
	MenuValuesOp* variableArray[size] = {arg1, args...};
	size_t memsize = size * sizeof(MenuValuesOp*);
	values = (MenuValuesOp**)malloc(memsize);
	memcpy(values, variableArray, memsize);
}
template <typename... Ts>
MenuValue::MenuValue(const char * _title, MenuValuesOp& arg1, Ts...args) :
	MenuValue(_title, &arg1, &args...)
{}

template <typename numberType>
String MenuValues<numberType>::getValueAsString() {
	return String(variable);
}

template <typename numberType>
MenuValues<numberType>& MenuValues<numberType>::setMin(numberType _min) {
	min = _min;
	if (variable < _min) {
		variable = _min;
	}
	return *this;
}

template <typename numberType>
MenuValues<numberType>& MenuValues<numberType>::setMax(numberType _max) {
	max = _max;
	if (variable > _max) {
		variable = _max;
	}
	return *this;
}

template <typename numberType>
void MenuValues<numberType>::increment() {
	if (variable + inc >= max) {
		variable = max;
	} else {
		variable += inc;
	}
}

template <typename numberType>
void MenuValues<numberType>::decrement() {
	if (variable - inc <= min) {
		variable = min;
	} else {
		variable -= inc;
	}
}

template <typename numberType>
bool MenuValues<numberType>::valueHasChanged() {
	bool changed = (variable != lastValue);
	lastValue = variable;
	return changed;
}
