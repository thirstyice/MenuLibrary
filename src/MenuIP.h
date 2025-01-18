#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

class MenuIP : public MenuValue {
public:
	MenuIP(String _title, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet, MenuCore* after = nullptr);
	MenuIP(String _title, IPAddress* ip, MenuCore* after = nullptr);
	MenuIP(String _title, uint32_t* ip, MenuCore* after = nullptr);
	MenuIP(String _title, uint8_t* array, MenuCore* after = nullptr);
private:
	const bool isBigEndian();
};
