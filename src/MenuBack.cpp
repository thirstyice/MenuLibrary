#include "MenuBack.h"

MenuBackClass MenuBack;

String MenuBackClass::getTitle() const {
	return String(MenuChar[MenuChars::BackArrow]) + title;
}