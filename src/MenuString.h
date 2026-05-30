#pragma once

#include "MenuBase.h"

/**
** @brief Defines a Menu item that can edit a String
**
**/
class MenuString: public MenuBase<MenuString> {
public:
	/**
	 * @brief Create a MenuString
	 * @param _title The title to show before the editable string
	 * @param str The editable string
	 */
	MenuString(const char* _title, String& str) : MenuBase(_title), string(str) {}
	/**
	** @brief Change the editable String
	**
	** @param str The new String variable
	** @return ** MenuString& Allows method chaining
	**/
	MenuString& setString(String& str);
	/**
	** @brief Set the maximum length of the editable String
	**
	** @param len The new max length
	** @return ** MenuString& Allows method chaining
	**/
	MenuString& setMaxLength(uint8_t len);
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
	bool needsRedraw() override;
private:
	String& string;
	uint8_t maxLength=0;
	String lastValue;
	uint8_t index = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
};