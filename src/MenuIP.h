#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP final : public MenuValue {
public:
	MenuIP(String _title, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet);
	MenuIP(String _title, IPAddress* ip);
};
