#pragma once

#include "MenuItem.h"
#include "Menu.h"
#include "MenuToggle.h"
#include "MenuValue.h"
#include "MenuBack.h"
#include "MenuIP.h"
#include "MenuString.h"

#define TITLEDEF(id, title) const char PROGMEM id##Title[] = title;
#define MENUITEMDEFBEGIN(type, id, title, previousItem) TITLEDEF(id, title); type id{id##Title, &previousItem

#define MENU(id, title, previousItem, selectedItem, ...) __VA_ARGS__ MENUITEMDEFBEGIN(id, title, previousItem), &selectedItem};
#define TOPMENU(id, title, selectedItem, ...) MENU(id, title, nullptr, selectedItem __VA_ARGS__)

#define MENUITEM(id, title, previousItem) MENUITEMDEFBEGIN(MenuItem, id, title, previousItem)};
#define MENUBACK(id, title, previousItem) MENUITEMDEFBEGIN(MenuBack, id, title, previousItem)};

#define MENUTOGGLE(id, title, previousItem, variable) bool variable; MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable};
#define MENUTOGGLE(id, title, previousItem, variable, initValue) bool variable = initValue; MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable};
#define MENUTOGGLE(id, title, previousItem, variable, trueString, falseString) bool variable; TITLEDEF(id##True, trueString) TITLEDEF(id##False, falseString) MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable, &id##TrueTitle, &id##FalseTitle};
#define MENUTOGGLE(id, title, previousItem, variable, initValue, trueString, falseString) bool variable = initValue; TITLEDEF(id##True, trueString) TITLEDEF(id##False, falseString) MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable, &id##TrueTitle, &id##FalseTitle};


#define MENUSTRING(id, title, previousItem, variable) String variable; MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable};
#define MENUSTRING(id, title, previousItem, variable, initValue) String variable = initValue; MENUITEMDEFBEGIN(MenuItem, id, title, previousItem), &variable};

#define MENUIP(id, title, previousItem, variable) IPAddress variable; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIP(id, title, previousItem, variable, initValue) IPAddress variable = initValue; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIP32(id, title, previousItem, variable) uint32_t variable; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIP32(id, title, previousItem, variable, initValue) uint32_t variable = initValue; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIPARRAY(id, title, previousItem, array) uint8_t array[4]; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), array};
#define MENUIPARRAY(id, title, previousItem, array, initValue) uint8_t array[4] = initValue; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), array};
