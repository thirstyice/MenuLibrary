#include "MenuBack.h"

MenuBack MenuBackDefault;

String MenuBack::getTitle() {
	return String(MenuChar[MenuChars::BackArrow]) + title;
}