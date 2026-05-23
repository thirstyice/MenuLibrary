#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP : public MenuValue {
public:
	MenuIP(const char * _title, uint8_t& firstOctet, uint8_t& secondOctet, uint8_t& thirdOctet, uint8_t& fourthOctet);
	MenuIP(const char * _title, IPAddress& ip);
	MenuIP(const char * _title, uint32_t& ip);
private:
	const bool isBigEndian();
};
