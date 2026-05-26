#include "MenuBack.h"

MenuBack MenuBackDefault;

TitleFlags MenuBack::getTitle(char * buf, const uint8_t& len) {
	TitleFlags flags;
	hasChanges = false;
	flags.specialType = TitleFlags::SpecialTypes::Back;
	strlcpy(buf, title, len);
	return flags;
}