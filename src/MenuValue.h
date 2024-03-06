#pragma once

#include "MenuOp.h"

template <typename numberType>
class MenuValue : public MenuOp {
public:
	struct MenuValues {
		numberType* variable = nullptr;
		numberType max = 1;
		numberType min = 0;
		numberType inc = 1;
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
	};
	template <typename... args>
	MenuValue(String _title, args...variables) {
		title = _title;
		size = sizeof...(variables);
		MenuValues variableArray[size] = {variables...}; 
		size_t memsize = size * sizeof(MenuValues);
		values = (MenuValues*)malloc(memsize);
		memcpy(values, variableArray, memsize);
	}
	void setVariable(numberType* _variable, uint8_t index=0) {values[index].variable = _variable;}
	void setMax(numberType _max, uint8_t index = 0);
	void setMin(numberType _min, uint8_t index = 0);
	void setIncrement(numberType _inc, uint8_t index = 0) {values[index].inc = _inc;}
	String getTitle();

private:
	bool active = false;
	uint8_t selected = 0;
	uint8_t size = 0;
	virtual bool handleEnter();
	virtual bool handleExit();
	virtual bool handleScrollNext();
	virtual bool handleScrollPrevious();
	MenuValues* values;
};


template<typename numberType>
void MenuValue<numberType>::setMin(numberType _min, uint8_t index) {
	values[index].min = _min;
	if (*values[index].variable < _min) {
		*values[index].variable = _min;
	}
}

template<typename numberType>
void MenuValue<numberType>::setMax(numberType _max, uint8_t index) {
	values[index].max = _max;
	if (*values[index].variable > _max) {
		*values[index].variable = _max;
	}
}

template<typename numberType>
bool MenuValue<numberType>::handleEnter() {
	selected = 0;
	active = true;
	return true;
}

template<typename numberType>
bool MenuValue<numberType>::handleExit() {
	selected --;
	if (selected == 0) {
		active = false;
		return true;
	}
	return false;
}

// TODO handle click

template<typename numberType>
bool MenuValue<numberType>::handleScrollNext() {
	if (*values[selected].variable + values[selected].inc >= values[selected].max) {
		*values[selected].variable = values[selected].max;
	} else {
		*values[selected].variable += values[selected].inc;
	}
	return false;
}

template<typename numberType>
bool MenuValue<numberType>::handleScrollPrevious() {
	if (*values[selected].variable - values[selected].inc <= values[selected].min) {
		*values[selected].variable = values[selected].min;
	} else {
		*values[selected].variable -= values[selected].inc;
	}
	return false;
}

template <typename numberType>
String MenuValue<numberType>::getTitle() {
	String valuesString = "";
	for (uint8_t i=0; i<size; i++) {
		String variableString = String(*values[i].variable);
		if (active == true && selected == i) {
			variableString = String('\17') + variableString + String('\16');
		}
		valuesString += variableString;
	}
	return (title + "\t" + valuesString);
}


