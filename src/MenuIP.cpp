#include "MenuIP.h"

MenuIP::MenuIP(String _title, uint8_t* firstOctet, uint8_t* secondOctet, uint8_t* thirdOctet, uint8_t* fourthOctet) {
	setSeparator('.');
	init(_title, 
		new MenuValues<uint8_t>(firstOctet, 255, 0, 1),
		new MenuValues<uint8_t>(secondOctet, 255, 0, 1),
		new MenuValues<uint8_t>(thirdOctet, 255, 0, 1),
		new MenuValues<uint8_t>(fourthOctet, 255, 0, 1)
	);
}