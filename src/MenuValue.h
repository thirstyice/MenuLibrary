#pragma once

#include "MenuOp.h"


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
	void setVariable(numberType* _variable) {variable = _variable;}
	void setMax(numberType _max);
	void setMin(numberType _min);
	void setIncrement(numberType _inc) {inc = _inc;}
};

class MenuValue : public MenuOp {
public:
	MenuValue() {};
	template <typename... args>
	MenuValue(String _title, args...variables) {init(_title, variables...);}
	~MenuValue();
	String getTitle();
	bool needsRedraw();
	void setSeparator(char _separator);

protected:
	template <typename... args>
	void init(String _title, args...variables);
private:
	char separator = ' ';
	uint8_t selected = 0;
	uint8_t size = 0;
	MenuEvent::Event handleClick();
	MenuEvent::Event handleBack();
	MenuEvent::Event handleScrollNext();
	MenuEvent::Event handleScrollPrevious();
	MenuValuesOp** values;
};

template <typename... args>
void MenuValue::init(String _title, args...variables) {
	title = _title;
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
void MenuValues<numberType>::setMin(numberType _min) {
	min = _min;
	if (*variable < _min) {
		*variable = _min;
	}
}

template <typename numberType>
void MenuValues<numberType>::setMax(numberType _max) {
	max = _max;
	if (*variable > _max) {
		*variable = _max;
	}
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




