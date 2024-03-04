#pragma once

#include "MenuOp.h"

template <typename numberType>
class MenuValue : public MenuOp {
public:
	MenuValue() {};
	MenuValue(
		String _title,
		numberType* _variable,
		numberType _max = 1,
		numberType _min = 0,
		numberType _increment = 1
	) : variable{_variable},
		max{_max},
		min{_min},
		inc{_increment}
		{title = _title;}
	void setVariable(numberType* _variable) {variable = _variable;}
	void setMax(numberType _max);
	void setMin(numberType _min);
	void setIncrement(numberType _inc) {inc = _inc;}
	String getTitle();
private:
	numberType* variable = nullptr;
	numberType max = 1;
	numberType min = 0;
	numberType inc = 1;
	bool selected = false;
	virtual bool handleEnter();
	virtual bool handleExit();
	virtual bool handleScrollNext();
	virtual bool handleScrollPrevious();
};


template<typename numberType>
void MenuValue<numberType>::setMin(numberType _min) {
	min = _min;
	if (*variable < min) {
		*variable = min;
	}
}

template<typename numberType>
void MenuValue<numberType>::setMax(numberType _max) {
	max = _max;
	if (*variable > max) {
		*variable = max;
	}
}

template<typename numberType>
bool MenuValue<numberType>::handleEnter() {
	selected = true;
	return true;
}

template<typename numberType>
bool MenuValue<numberType>::handleExit() {
	selected = false;
	return false;
}

template<typename numberType>
bool MenuValue<numberType>::handleScrollNext() {
	if (*variable + inc >= max) {
		*variable = max;
	} else {
		*variable += inc;
	}
	return false;
}

template<typename numberType>
bool MenuValue<numberType>::handleScrollPrevious() {
	if (*variable - inc <= min) {
		*variable = min;
	} else {
		*variable -= inc;
	}
	return false;
}

template <typename numberType>
String MenuValue<numberType>::getTitle() {
	String variableString = String(*variable);
	if (selected) {
		variableString = String('\17') + variableString + String('\16');
	}
	return (title + "\t" + variableString);
}


