/*******************************************************************************
* Project: MenuLibrary                                                         *
* Filename: /src/MenuDisp.h                                                    *
*                                                                              *
* Created: 2026-06-03                                                          *
* Author: thirstyice                                                           *
*                                                                              *
* Copyright (c) 2026 Tauran - https://github.com/thirstyice                    *
* For details see MenuLibrary/LICENSE (if applicable)                          *
*                                                                              *
*******************************************************************************/

#include "MenuItem.h"


template <typename T>
class MenuDispBase : public MenuItem {
protected:
	T& val;
	T lastVal;
	TitleFlags getTitle(char* buf, const uint8_t& len) override {
		TitleFlags flags;
		hasChanges = false;
		lastVal = val;
		strlcpy(buf, title, len);
		flags.alignRightFrom = strlen(buf);
		strlcat(buf, getVarAsString().c_str(), len);
		return flags;
	}
	bool needsRedraw() override {
		return (val != lastVal) || hasChanges;
	}
	virtual String getVarAsString() =0;
public:
	MenuDispBase(const char* _title, T& _var) : MenuItem(_title), val(_var) {}
};

/**
 * @brief Defines a Menu item for displaying the value of a variable
 * @tparam T The type of the variable to display
 */
template <typename T>
class MenuDisp : public MenuDispBase<T> {
	using MenuDispBase<T>::MenuDispBase;
	String getVarAsString() override {return String(MenuDispBase<T>::val);}
};

/**
 * @brief Defines a Menu item for displaying the value of a String
 */
template <>
class MenuDisp<String> : public MenuDispBase<String> {
	using MenuDispBase<String>::MenuDispBase;
	String getVarAsString() override {return val;}
};

#include <IPAddress.h>

/**
 * @brief Defines a Menu item for displaying the value of an IPAddress
 */
template <>
class MenuDisp<IPAddress> : public MenuDispBase<IPAddress> {
	using MenuDispBase<IPAddress>::MenuDispBase;
	String getVarAsString() override {
		char ipStr[] = "xxx.xxx.xxx.xxx"; // toString only exists on ESP
		sprintf(ipStr, "%d.%d.%d.%d", val[0], val[1], val[2], val[3]);
		return String(ipStr);
	}
};