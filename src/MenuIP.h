#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP : public MenuValue {
public:
	MenuIP(uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet);
	MenuIP(IPAddress* ip);
	MenuIP(uint32_t* ip);
private:
	const bool isBigEndian();
};
