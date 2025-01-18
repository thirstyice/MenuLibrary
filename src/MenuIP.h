#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP : public MenuValues {
private:
	const bool isBigEndian();
	MenuValue<uint8_t> addressValues[4];
public:
	MenuIP(const char* _title, MenuCore* after, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet);
	MenuIP(const char* _title, MenuCore* after, IPAddress* ip);
	MenuIP(const char* _title, MenuCore* after, uint32_t* ip);
	MenuIP(const char* _title, MenuCore* after, uint8_t* array);
};
