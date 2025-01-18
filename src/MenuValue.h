#pragma once

#include "MenuBase.h"


class MenuValuesOp {
public:
	virtual String getValueAsString() =0;
	virtual void increment() =0;
	virtual void decrement() =0;
	virtual bool valueHasChanged() =0;
	virtual ~MenuValuesOp() {};
};

template <typename numberType>
class MenuValues : public MenuValuesOp {
private:
	numberType* variable = nullptr;
	numberType lastValue;
	numberType max = 1;
	numberType min = 0;
	numberType inc = 1;
public:
	MenuValues() {}
	MenuValues(
		numberType* _variable,
		numberType _max = 1,
		numberType _min = 0,
		numberType _increment = 1
	) :
		variable{_variable},
		max{_max},
		min{_min},
		inc{_increment}
	{}
	String getValueAsString();
	void increment();
	void decrement();
	bool valueHasChanged();
	MenuValues& setVariable(numberType* _variable) {variable = _variable; return *this;}
	MenuValues& setMax(numberType _max);
	MenuValues& setMin(numberType _min);
	MenuValues& setIncrement(numberType _inc) {inc = _inc; return *this;}
};

class MenuValue : public MenuBase<MenuValue> {
public:
	template <typename... args>
	MenuValue(const char* _title, MenuCore* after = nullptr, args...variables);
	MenuValue(const MenuValue &);
	~MenuValue();
	String getTitle();
	bool needsRedraw();
	MenuValue* setSeparator(char _separator);

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

template <typename... args>
MenuValue::MenuValue(const char* _title, MenuCore* after, args...variables) : MenuBase(_title, after) {
	size = sizeof...(variables);
	MenuValuesOp* variableArray[size] = {variables...};
	size_t memsize = size * sizeof(MenuValuesOp*);
	values = (MenuValuesOp**)malloc(memsize);
	memcpy(values, variableArray, memsize);
}

template <typename numberType>
String MenuValues<numberType>::getValueAsString() {
	return String(*variable);
}

template <typename numberType>
MenuValues<numberType>& MenuValues<numberType>::setMin(numberType _min) {
	min = _min;
	if (*variable < _min) {
		*variable = _min;
	}
	return *this;
}

template <typename numberType>
MenuValues<numberType>& MenuValues<numberType>::setMax(numberType _max) {
	max = _max;
	if (*variable > _max) {
		*variable = _max;
	}
	return *this;
}

template <typename numberType>
void MenuValues<numberType>::increment() {
	if (*variable + inc >= max) {
		*variable = max;
	} else {
		*variable += inc;
	}
}

template <typename numberType>
void MenuValues<numberType>::decrement() {
	if (*variable - inc <= min) {
		*variable = min;
	} else {
		*variable -= inc;
	}
}

template <typename numberType>
bool MenuValues<numberType>::valueHasChanged() {
	bool changed = (*variable != lastValue);
	lastValue = *variable;
	return changed;
}
