#pragma once

#include "MenuBase.h"


class MenuValueOp {
public:
	virtual String getValueAsString() =0;
	virtual void increment() =0;
	virtual void decrement() =0;
	virtual bool valueHasChanged() =0;
	void setNext(MenuValueOp* element) {next=element;}
	void setPrev(MenuValueOp* element) {prev=element;}
	MenuValueOp* getNext() {return next;}
	MenuValueOp* getPrev() {return prev;}
	virtual ~MenuValueOp() {};
private:
	MenuValueOp* next = nullptr;
	MenuValueOp* prev = nullptr;
};

template <typename numberType>
class MenuValue : public MenuValueOp {
private:
	numberType* variable = nullptr;
	numberType lastValue;
	numberType max = 1;
	numberType min = 0;
	numberType inc = 1;
	MenuValueOp* next = nullptr;
	MenuValueOp* prev = nullptr;
public:
	MenuValue() {}
	MenuValue(
		numberType* _variable,
		MenuValueOp* after,
		numberType _max = 1,
		numberType _min = 0,
		numberType _increment = 1
	) :
		variable{_variable},
		max{_max},
		min{_min},
		inc{_increment}
	{if(after){insertAfter(after);}}
	String getValueAsString();
	void increment();
	void decrement();
	MenuValue& insertAfter(MenuValueOp*);
	MenuValue& insertBefore(MenuValueOp*);
	bool valueHasChanged();
	MenuValue& setVariable(numberType* _variable) {variable = _variable; return *this;}
	MenuValue& setMax(numberType _max);
	MenuValue& setMin(numberType _min);
	MenuValue& setIncrement(numberType _inc) {inc = _inc; return *this;}
};

class MenuValues : public MenuBase<MenuValues> {
public:
	MenuValues(const char* _title, MenuCore* after, MenuValueOp* firstElement);
	String getTitle();
	bool needsRedraw();
	MenuValues* setSeparator(char _separator);

private:
	char separator = ' ';
	MenuReaction engage();
	MenuReaction disengage();
	MenuReaction increase();
	MenuReaction decrease();
	MenuValueOp* selected;
};

MenuValues::MenuValues(const char* _title, MenuCore* after, MenuValueOp* firstElement) :
	MenuBase(_title, after),
	selected(firstElement)
{}

template <typename numberType>
String MenuValue<numberType>::getValueAsString() {
	return String(*variable);
}

template <typename numberType>
MenuValue<numberType>& MenuValue<numberType>::setMin(numberType _min) {
	min = _min;
	if (*variable < _min) {
		*variable = _min;
	}
	return *this;
}

template <typename numberType>
MenuValue<numberType>& MenuValue<numberType>::setMax(numberType _max) {
	max = _max;
	if (*variable > _max) {
		*variable = _max;
	}
	return *this;
}

template <typename numberType>
void MenuValue<numberType>::increment() {
	if (*variable + inc >= max) {
		*variable = max;
	} else {
		*variable += inc;
	}
}

template <typename numberType>
void MenuValue<numberType>::decrement() {
	if (*variable - inc <= min) {
		*variable = min;
	} else {
		*variable -= inc;
	}
}

template <typename numberType>
bool MenuValue<numberType>::valueHasChanged() {
	bool changed = (*variable != lastValue);
	lastValue = *variable;
	return changed;
}

template <typename numberType>
MenuValue<numberType>& MenuValue<numberType>::insertAfter(MenuValueOp* element) {
	setPrev(element);
	setNext(element->getNext());
	element->getNext()->setPrev((MenuValueOp*)this);
	element->setNext((MenuValueOp*)this);
	return *this;
}

template <typename numberType>
MenuValue<numberType>& MenuValue<numberType>::insertBefore(MenuValueOp* element) {
	setNext(element);
	setPrev(element->getPrev());
	element->getPrev()->setNext((MenuValueOp*)this);
	element->setPrev((MenuValueOp*)this);
	return *this;
}