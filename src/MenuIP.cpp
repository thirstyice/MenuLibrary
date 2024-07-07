#include "MenuIP.h"

const bool MenuIP::isBigEndian() {
	union {
		uint32_t i;
		char c[4];
	} u = {0x00000001};
	return (u.c[0]==1);
}

MenuIP::MenuIP(uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet) :
	MenuValue(
		new MenuValues<uint8_t>(firstOctet, 255, 0, 1),
		new MenuValues<uint8_t>(secondOctet, 255, 0, 1),
		new MenuValues<uint8_t>(thirdOctet, 255, 0, 1),
		new MenuValues<uint8_t>(fourthOctet, 255, 0, 1)
	)
{
	setSeparator('.');
}

MenuIP::MenuIP(IPAddress* ip) {
	MenuIP(&ip->operator[](0), &ip->operator[](1), &ip->operator[](2), &ip->operator[](3));
}

MenuIP::MenuIP(uint32_t* ip) {
	uint8_t* ptr = (uint8_t*)ip;
	if (isBigEndian()) {
		MenuIP(ptr+3, ptr+2, ptr+1, ptr);
	} else {
		MenuIP(ptr, ptr+1, ptr+2, ptr+3);
	}
}