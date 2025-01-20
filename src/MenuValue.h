#pragma once

#include "MenuBase.h"


class MenuValueOp {
public:
	virtual String getValueAsString() const =0;
	virtual void increment() const =0;
	virtual void decrement() const =0;
	virtual bool valueHasChanged() =0;
	void setNext(MenuValueOp* element) {next=element;}
	void setPrev(MenuValueOp* element) {prev=element;}
	MenuValueOp* getNext() const {return next;}
	MenuValueOp* getPrev() const {return prev;}
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
	String getValueAsString() const override;
	void increment() const override;
	void decrement() const override;
	void insertAfter(MenuValueOp*);
	void insertBefore(MenuValueOp*);
	bool valueHasChanged() override;
	void setVariable(numberType* _variable) {variable = _variable;}
	void setMax(numberType _max);
	void setMin(numberType _min);
	void setIncrement(numberType _inc) {inc = _inc;}
};

class MenuValues : public MenuBase {
public:
	MenuValues(const char* _title, MenuCore* after, MenuValueOp* firstElement);
	String getTitle() override;
	bool needsRedraw() override;
	MenuValues* setSeparator(char _separator);

private:
	char separator = ' ';
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
	MenuValueOp* selected;
};

template <typename numberType>
String MenuValue<numberType>::getValueAsString() const {
	return String(*variable);
}

template <typename numberType>
void MenuValue<numberType>::setMin(numberType _min) {
	min = _min;
	if (*variable < _min) {
		*variable = _min;
	}
}

template <typename numberType>
void MenuValue<numberType>::setMax(numberType _max) {
	max = _max;
	if (*variable > _max) {
		*variable = _max;
	}
}

template <typename numberType>
void MenuValue<numberType>::increment() const {
	if (*variable + inc >= max) {
		*variable = max;
	} else {
		*variable += inc;
	}
}

template <typename numberType>
void MenuValue<numberType>::decrement() const {
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
void MenuValue<numberType>::insertAfter(MenuValueOp* element) {
	setPrev(element);
	setNext(element->getNext());
	element->getNext()->setPrev((MenuValueOp*)this);
	element->setNext((MenuValueOp*)this);
}

template <typename numberType>
void MenuValue<numberType>::insertBefore(MenuValueOp* element) {
	setNext(element);
	setPrev(element->getPrev());
	element->getPrev()->setNext((MenuValueOp*)this);
	element->setPrev((MenuValueOp*)this);
}