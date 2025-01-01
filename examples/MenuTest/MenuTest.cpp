#include <Arduino.h>

#include <MenuLibrary.h>

#include <MenuOutput/Olimex16x2.h>

int freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

Olimex16x2 lcd;

bool buttonState[4];
MenuAction buttonMapping[4] = {
	MenuAction::disengage,
	MenuAction::decrease,
	MenuAction::increase,
	MenuAction::engage
};

bool toggleTest = false;
uint8_t valueTest = 0;
float valueTestFloat = 1;
uint8_t ipTest1[] = {192,168,0,1};
uint32_t ipTest2 = 0x12345678;
String stringTest = "Hello World!";
String shortStr = "Short!";

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
	Serial.print(ipTest1[0]);
	Serial.print('.');
	Serial.print(ipTest1[1]);
	Serial.print('.');
	Serial.print(ipTest1[2]);
	Serial.print('.');
	Serial.println(ipTest1[3]);

	Serial.print("IP 2 is now: ");
	Serial.println(ipTest2);

	Serial.print("String is now: ");
	Serial.println(stringTest);

	Serial.print("Str is now: ");
	Serial.println(shortStr);

	Serial.print("Free Ram:");
	Serial.println(freeRam());
}

// Define all items;
Menu menu("top");
MenuItem menuTitle("MenuLibrary Test");
MenuItem menuPrint("Print values", &menuTitle);
Menu submenu("Submenu", &menuPrint);
	MenuBack submenuBack;
	MenuItem submenuBackText("Change Back Text", &submenuBack);
	MenuItem submenuHello("Hello", &submenuBackText);
	MenuItem submenuWorld("World", &submenuWorld);
	MenuItem submenuPrint("Print from submenu", &submenuWorld);
Menu menuSmall("Small submenu, big title", &submenu);
	MenuBack menuSmallBack;
MenuToggle menuOverridden("overridden", &toggleTest, &menuSmall);
MenuValues<uint8_t> menuValueTest(&valueTest, 255);
MenuValues<float> menuValueTestFloat(&valueTestFloat, 1,0,0.1);
MenuValue menuValue("Value", &menuOverridden, &menuValueTest, &menuValueTestFloat);
MenuIP menuIp8x4("IP(8x4)", &ipTest1[0], &ipTest1[1], &ipTest1[2], &ipTest1[3], &menuValue);
MenuIP menuIp32("IP(32)", &ipTest2, &menuIp8x4);
MenuString menuString("String:", &stringTest, &menuIp32);
MenuString menuStr("Str:", &shortStr, &menuString);

// Add additional functionality
void changeBackText(MenuItem*) {
	submenuBack.setTitle("Back (changed)");
}
void menuInit() {
	menu.setFocusedItem(&menuTitle);
	menuPrint.setResponder(printValues, MenuAction::engage);
	submenu.setFocusedItem(&submenuBack);
	submenuBackText.setResponder(changeBackText, MenuAction::engage);
	submenuPrint.setResponder(printValues, MenuAction::engage);
	menuOverridden.setTitle("Toggle");
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
	menu.setOutput(outputs,1);
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
				menu.doAction(buttonMapping[i]);
			}
		}
	}
}

void loop() {
	doButtons();
	menu.doDraw();
}