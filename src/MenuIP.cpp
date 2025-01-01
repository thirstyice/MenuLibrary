#include "MenuIP.h"

const bool MenuIP::isBigEndian() {
	union {
		uint32_t i;
		char c[4];
	} u = {0x00000001};
	return (u.c[0]==1);
}

MenuIP::MenuIP(String _title, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet, MenuCore* after) :
	MenuValue(
		_title,
		after,
		new MenuValues<uint8_t>(firstOctet, 255, 0, 1),
		new MenuValues<uint8_t>(secondOctet, 255, 0, 1),
		new MenuValues<uint8_t>(thirdOctet, 255, 0, 1),
		new MenuValues<uint8_t>(fourthOctet, 255, 0, 1)
	)
{
	setSeparator('.');
}

MenuIP::MenuIP(String _title, IPAddress* ip, MenuCore* after) :
	MenuIP(_title, &ip->operator[](0), &ip->operator[](1), &ip->operator[](2), &ip->operator[](3), after)
{}


MenuIP::MenuIP(String _title, uint32_t* ip, MenuCore* after) :
	MenuIP(_title,
		isBigEndian()?((uint8_t*)ip)+3:((uint8_t*)ip)+0,
		isBigEndian()?((uint8_t*)ip)+2:((uint8_t*)ip)+1,
		isBigEndian()?((uint8_t*)ip)+1:((uint8_t*)ip)+2,
		isBigEndian()?((uint8_t*)ip)+0:((uint8_t*)ip)+3,
		after
	)
{}