#include <Arduino.h>

#include <MenuLibrary.h>

#include <MenuOutput/Olimex16x2.h>

int freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

Olimex16x2 lcd;

TOPMENU(mainMenu, "-", &title,
	MENUITEM(title, "MenuLibrary Test", nullptr)
	MENUITEM(menuPrint, "Print Values", &title)
	MENU(submenu, "Submenu", &menuPrint, &submenuBack,
		MENUBACK(submenuBack, nullptr)
		MENUITEM(submenuHello, "Hello", &submenuBack)
		MENUITEM(submenuWorld, "World", &submenuHello)
		MENUITEM(submenuPrint, "Print from Submenu", &submenuWorld)
	)
	MENU(menuSmall, "Small submenu, big title", &submenu, &menuSmallBack,
		MENUBACK(menuSmallBack, nullptr)
	)
	MENUTOGGLE(menuToggle, "Toggle", &menuSmall, toggleTest, false, "Yes", "No")
	MENUVALUES(menuValues, "Values", &menuToggle, &valueTestMenuValue,
		MENUVALUE(nullptr, uint8_t, valueTest, 0, 255, 0, 1)
		MENUVALUE(&valueTestMenuValue, float, valueTestFloat, 0, 1, 0, 0.01)
	)
	MENUIPARRAY(menuIp8x4, "IP(8x4)", &menuValues, ipTest1, 192,168,0,1)
	MENUIP32(menuIp32, "IP(32)", &menuIp8x4, ipTest2, 0x12345678)
	MENUSTRING(menuString, "String", &menuIp32, stringTest, "Hello World!")
	MENUSTRING(menuStr, "Str", &menuString, shortStr, "Short!")
)

bool buttonState[4];
MenuAction buttonMapping[4] = {
	MenuAction::disengage,
	MenuAction::decrease,
	MenuAction::increase,
	MenuAction::engage
};

void printValues(MenuItem* caller) {
	Serial.print("Called by: ");
	Serial.println(caller->getTitle());
	Serial.print(F("Toggle is now: "));
	Serial.println(toggleTest);

	Serial.print("Values are now: ");
	Serial.print(valueTest);
	Serial.print(", ");
	Serial.println(valueTestFloat);

	Serial.print("IP 1 is now: ");
	//Serial.print(ipTest1[0]);
	Serial.print('.');
	//Serial.print(ipTest1[1]);
	Serial.print('.');
	//Serial.print(ipTest1[2]);
	Serial.print('.');
	//Serial.println(ipTest1[3]);

	Serial.print("IP 2 is now: ");
	//Serial.println(ipTest2);

	Serial.print("String is now: ");
	Serial.println(stringTest);

	Serial.print("Str is now: ");
	Serial.println(shortStr);

	Serial.print("Free Ram:");
	Serial.println(freeRam());
}

void menuInit() {
	menuPrint.setResponder(printValues, MenuAction::engage);
	submenuPrint.setResponder(printValues, MenuAction::engage);
};


MenuOutput* outputs[] = {
	new MenuOutputOlimex16x2(&lcd)
};

void setup() {
	Serial.begin(115200);
	Serial.println("Begin");
	lcd.begin();
	lcd.setBacklight(255);
	lcd.clear();
	menuInit();
	mainMenu.setOutput(outputs,1);
}

void doButtons() {
	uint8_t buttons = lcd.readAllButtons();
	for (uint8_t i=0; i<4; i++) {
		uint8_t currentButton = (buttons>>i)&1;
		if (currentButton==1) { // 1 == not pressed
			buttonState[i] = false;
			continue;
		} else {
			if (buttonState[i] == false) {
				buttonState[i] = true;
				mainMenu.doAction(buttonMapping[i]);
			}
		}
	}
}

void loop() {
	doButtons();
	mainMenu.doDraw();
}