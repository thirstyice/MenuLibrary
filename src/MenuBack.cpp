#include "MenuBack.h"

MenuBackClass MenuBack;

String MenuBackClass::getTitle() {
	return String(MenuChar[MenuChars::BackArrow]) + title;
}