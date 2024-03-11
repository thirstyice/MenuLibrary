#pragma once

#include "MenuOp.h"


class MenuValuesOp {
public:
	virtual String getValueAsString() =0;
	virtual void increment() =0;
	virtual void decrement() =0;
};

template <typename numberType>
class MenuValues : MenuValuesOp {
private:
	numberType* variable = nullptr;
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
	String getValueAsString() {return String(variable*);}
	void increment();
	void decrement();
	void setVariable(numberType* _variable) {variable = _variable;}
	void setMax(numberType _max);
	void setMin(numberType _min);
	void setIncrement(numberType _inc) {inc = _inc;}
};

class MenuValue : public MenuOp {
public:
	template <typename... args>
	~MenuValue();
	String getTitle() const;
	void setSeparator(char _separator) {separator = _separator;}

private:
	char separator = ' ';
	uint8_t selected = 0;
	uint8_t size = 0;
	virtual MenuEvent::Event handleClick();
	virtual MenuEvent::Event handleBack();
	virtual MenuEvent::Event handleScrollNext();
	virtual MenuEvent::Event handleScrollPrevious();
	MenuValuesOp** values;
};


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




