#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP : public MenuValue {
public:
	MenuIP(const char* _title, MenuCore* after, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet);
	MenuIP(const char* _title, MenuCore* after, IPAddress* ip);
	MenuIP(const char* _title, MenuCore* after, uint32_t* ip);
	MenuIP(const char* _title, MenuCore* after, uint8_t* array);
private:
	const bool isBigEndian();
};
