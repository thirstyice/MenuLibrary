#pragma once

#include "MenuItem.h"
#include "Menu.h"
#include "MenuToggle.h"
#include "MenuValue.h"
#include "MenuBack.h"
#include "MenuIP.h"
#include "MenuString.h"

#define TITLEDEF(id, title) const char id##Title[] PROGMEM = title;
#define MENUITEMDEFBEGIN(type, id, title, previousItem) TITLEDEF(id, title) type id{id##Title, previousItem

#define MENU(id, title, previousItem, selectedItem, ...) __VA_ARGS__ MENUITEMDEFBEGIN(Menu, id, title, previousItem), selectedItem};
#define TOPMENU(id, title, selectedItem, ...) MENU(id, title, nullptr, selectedItem, __VA_ARGS__)

#define MENUITEM(id, title, previousItem) MENUITEMDEFBEGIN(MenuItem, id, title, previousItem)};
#define MENUBACK(id, previousItem) MENUITEMDEFBEGIN(MenuBack, id, "Back", previousItem)};

#define MENUTOGGLE(id, title, previousItem, variable, initValue, trueString, falseString) bool variable = initValue; TITLEDEF(id##True, trueString) TITLEDEF(id##False, falseString) MENUITEMDEFBEGIN(MenuToggle, id, title, previousItem), &variable, id##TrueTitle, id##FalseTitle};

#define MENUSTRING(id, title, previousItem, variable, initValue) String variable = initValue; MENUITEMDEFBEGIN(MenuString, id, title, previousItem), &variable};

#define MENUIP(id, title, previousItem, variable, initValue) IPAddress variable = initValue; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIP32(id, title, previousItem, variable, initValue) uint32_t variable = initValue; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), &variable};
#define MENUIPARRAY(id, title, previousItem, array, initValue0, initValue1, initValue2, initValue3) uint8_t array[4] = {initValue0, initValue1, initValue2, initValue3}; MENUITEMDEFBEGIN(MenuIP, id, title, previousItem), array};


#define MENUVALUE(previousItem, type, variable, initValue, max, min, increment) type variable = initValue; MenuValue<type> variable##MenuValue(&variable, previousItem, max, min, increment);
#define MENUVALUES(id, title, previousItem, selectedItem, ...) __VA_ARGS__ MENUITEMDEFBEGIN(MenuValues, id, title, previousItem), selectedItem};
