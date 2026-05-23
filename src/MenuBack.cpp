#include "MenuBack.h"

MenuBack MenuBackDefault;

MenuCore::TitleFlags MenuBack::getTitle(char * buf, const uint8_t& len) {
	TitleFlags flags;
	hasChanges = false;
	if (len <= 1) {
		return flags;
	};
	buf[0] = MenuChars::BackArrow;
	buf[1] = '\0';
	strlcat(buf, title, len);
	return flags;
}