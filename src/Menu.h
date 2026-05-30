#pragma once

#include "MenuBase.h"

/**
** @brief Defines a Menu item that contains a Menu
** (either the top-level menu, or a submenu)
**
**/
class Menu final : public MenuBase<Menu> {
public:
	bool doDraw() override;
	/**
	 * @brief Cofigure the output(s) for the menu
	 * @param outputArray The array containing pointers to each output
	 * @param outputCount The number of outputs in the array
	 * @return
	 */
	Menu& setOutput(MenuOutput** outputArray, uint8_t outputCount);
	/**
	 * @brief Create a Menu from an existing array of pointers to Menu items
	 * @param _title The title to show when the Menu is a submenu
	 * @param itemArray The array of pointers to Menu items
	 * @param itemCount The number of Menu items
	 */
	Menu(const char * _title, MenuCore** itemArray, uint8_t itemCount) : MenuBase(_title), numItems(itemCount), submenu(itemArray) {}
	Menu(MenuCore** itemArray, uint8_t count) : Menu("", itemArray, count) {}
	/**
	 * @brief Create a Menu directly from Menu items
	 * @param _title The title to show when the Menu is a submenu
	 * @param arg1 The first menu item
	 * @param ...args The rest of the menu items
	 */
	template <typename... Ts>
	Menu(const char * _title, MenuCore& arg1, Ts...args) : MenuBase(_title), needsFree(true) {
		numItems = sizeof...(args) + 1;
		MenuCore* itemArray[numItems] = {&arg1, &args...};
		size_t memsize = numItems * sizeof(MenuCore*);
		submenu = (MenuCore**)malloc(memsize);
		memcpy(submenu, itemArray, memsize);
	};

	template <typename... Ts>
	Menu(MenuCore& arg1, Ts...args) : Menu("", arg1, args...) {}
	/**
	* @brief Create a Menu directly from pointers to Menu items
	* @param _title The title to show when the Menu is a submenu
	* @param arg1 A pointer to the first menu item
	* @param ...args Pointers to the rest of the menu items
	*/
	template <typename... Ts>
	Menu(const char * _title, MenuCore* arg1, Ts...args) : MenuBase(_title), needsFree(true) {
		numItems = sizeof...(args) + 1;
		MenuCore* itemArray[numItems] = {arg1, args...};
		size_t memsize = numItems * sizeof(MenuCore*);
		submenu = (MenuCore**)malloc(memsize);
		memcpy(submenu, itemArray, memsize);
	};
	template <typename... Ts>
	Menu(MenuCore* arg1, Ts...args) : Menu("", arg1, args...) {}

	Menu() : Menu((MenuCore**)nullptr, 0) {}
	MenuReaction doAction(MenuAction) override;
	TitleFlags getTitle(char* buf, const uint8_t& len) override;
	~Menu();

protected:
	Menu(Menu& c);

private:
	void setOutput(MenuOutput** outputArray, uint8_t outputCount, bool isTopLevel) override;
	void setFocusedLine(uint8_t line);
	bool needsFree = false;
	bool forceNextDraw = true;
	bool submenuIsOpen = false;
	uint8_t focusedLine = 0;
	MenuOutput** outputs = nullptr;
	uint8_t numOutputs = 0;
	MenuReaction engage() override;
	MenuReaction disengage() override;
	MenuReaction increase() override;
	MenuReaction decrease() override;
	uint8_t numItems = 0;
	MenuCore** submenu = nullptr;
};
