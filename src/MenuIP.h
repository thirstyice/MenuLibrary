#pragma once

#include "MenuValue.h"

#include <IPAddress.h>

/**
** @brief Defines a Menu item for controlling an IPAddress (IPv4 only)
**
**/
class MenuIP : public MenuValue {
public:
	/**
	 * @brief Create a MenuIP referencing four uint8_t
	 * @param _title The title to show before the IP address
	 * @param firstOctet First byte of IP address
	 * @param secondOctet Second byte of IP address
	 * @param thirdOctet Third byte of IP address
	 * @param fourthOctet Fourth byte of IP address
	 */
	MenuIP(const char * _title, uint8_t& firstOctet, uint8_t& secondOctet, uint8_t& thirdOctet, uint8_t& fourthOctet);
	/**
	 * @brief Create a MenuIP referencing an IPAddress
	 * @param _title The title to show before the IP address
	 * @param ip The IPAddress to reference
	 */
	MenuIP(const char * _title, IPAddress& ip);
	/**
	* @brief Create a MenuIP referencing a uint32_t
	* @param _title The title to show before the IP address
	* @param ip The uint32_t representing the IP address
	*/
	MenuIP(const char * _title, uint32_t& ip);
private:
	const bool isBigEndian();
};
