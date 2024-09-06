#include "MenuBack.h"

MenuBack MenuBackDefault;

String MenuBack::getTitle() {
	hasChanges = false;
	return String(MenuChar[MenuChars::BackArrow]) + title;
}