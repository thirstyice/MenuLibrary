#pragma once

#include "MenuOp.h"

template <typename numberType, char separator = ' '>
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
	String getTitle() const;

private:
	uint8_t selected = 0;
	uint8_t size = 0;
	virtual MenuEvent::Event handleClick();
	virtual MenuEvent::Event handleBack();
	virtual MenuEvent::Event handleScrollNext();
	virtual MenuEvent::Event handleScrollPrevious();
	MenuValues* values;
};


template <typename numberType, char separator>
void MenuValue<numberType, separator>::setMin(numberType _min, uint8_t index) {
	values[index].min = _min;
	if (*values[index].variable < _min) {
		*values[index].variable = _min;
	}
}

template <typename numberType, char separator>
void MenuValue<numberType, separator>::setMax(numberType _max, uint8_t index) {
	values[index].max = _max;
	if (*values[index].variable > _max) {
		*values[index].variable = _max;
	}
}

template <typename numberType, char separator>
MenuEvent::Event MenuValue<numberType, separator>::handleBack() {
	if (selected == 0) {
		active = false;
		return MenuEvent::exit;
	}
	selected --;
	return MenuEvent::noEvent;
}

template <typename numberType, char separator>
MenuEvent::Event MenuValue<numberType, separator>::handleClick() {
	if (!active) {
		active=true;
		selected=0;
		return MenuEvent::enter;
	} else {
		selected++;
	}
	if (selected >= size) {
		active = false;
		return MenuEvent::exit;
	}
	return MenuEvent::noEvent;
}

template <typename numberType, char separator>
MenuEvent::Event MenuValue<numberType, separator>::handleScrollNext() {
	if (*values[selected].variable + values[selected].inc >= values[selected].max) {
		*values[selected].variable = values[selected].max;
	} else {
		*values[selected].variable += values[selected].inc;
	}
	return MenuEvent::noEvent;
}

template <typename numberType, char separator>
MenuEvent::Event MenuValue<numberType, separator>::handleScrollPrevious() {
	if (*values[selected].variable - values[selected].inc <= values[selected].min) {
		*values[selected].variable = values[selected].min;
	} else {
		*values[selected].variable -= values[selected].inc;
	}
	return MenuEvent::noEvent;
}

template <typename numberType, char separator>
String MenuValue<numberType, separator>::getTitle() const {
	String valuesString = "";
	for (uint8_t i=0; i<size; i++) {
		String variableString = String(*values[i].variable);
		if (active == true && selected == i) {
			variableString = String(MenuChar[MenuChars::StartOfSelection]) + variableString + String(MenuChar[MenuChars::EndOfSelection]);
		}
		valuesString += variableString + separator + String(MenuChar[MenuChars::ReplaceableWithCursor]);
	}
	valuesString.remove(valuesString.length()-2);
	return (title + MenuChar[MenuChars::AlignRightFollowing] + valuesString);
}


