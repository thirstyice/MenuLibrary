#include "MenuIP.h"

const bool MenuIP::isBigEndian() {
	union {
		uint32_t i;
		char c[4];
	} u = {0x00000001};
	return (u.c[0]==1);
}

MenuIP::MenuIP(const char* _title, MenuCore* after, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet) :
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

MenuIP::MenuIP(const char* _title, MenuCore* after, uint8_t* array) :
	MenuIP(_title, after, &array[0], &array[1], &array[2], &array[3])
{}

MenuIP::MenuIP(const char* _title, MenuCore* after, IPAddress* ip) :
	MenuIP(_title, after, &ip->operator[](0), &ip->operator[](1), &ip->operator[](2), &ip->operator[](3))
{}


MenuIP::MenuIP(const char* _title, MenuCore* after, uint32_t* ip) :
	MenuIP(_title, after,
		isBigEndian()?((uint8_t*)ip)+3:((uint8_t*)ip)+0,
		isBigEndian()?((uint8_t*)ip)+2:((uint8_t*)ip)+1,
		isBigEndian()?((uint8_t*)ip)+1:((uint8_t*)ip)+2,
		isBigEndian()?((uint8_t*)ip)+0:((uint8_t*)ip)+3
	)
{}