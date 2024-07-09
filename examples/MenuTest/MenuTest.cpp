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

void changeBackText(MenuItem*) {
	MenuBackDefault.setTitle("Back (changed)");
}

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

	Serial.print("Free Ram:");
	Serial.println(freeRam());
}


Menu menu{
	new MenuItem("MenuLibrary Test"),
	(new MenuItem("Print values"))->setResponder(printValues, MenuAction::engage),
	new Menu("Submenu",
		&MenuBackDefault,
		(new MenuItem("Change Back Text"))->setResponder(changeBackText, MenuAction::engage),
		new MenuItem("Hello"),
		new MenuItem("World"),
		(new MenuItem("Print from submenu"))->setResponder(printValues, MenuAction::engage)
	),
	(new MenuToggle("overridden"))->setTitle("Toggle:")->setVar(&toggleTest),
	new MenuValue("Value",
		new MenuValues<uint8_t>(&valueTest, 255),
		new MenuValues<float>(&valueTestFloat, 1, 0, 0.1)
	),
	new MenuIP("IP(8x4):", &ipTest1[0], &ipTest1[1], &ipTest1[2], &ipTest1[3]),
	new MenuIP("IP(32):", &ipTest2),
	new MenuString("String:", &stringTest)
};


MenuOutput* outputs[] = {
	new MenuOutputOlimex16x2(&lcd)
};

void setup() {
	Serial.begin(9600);
	lcd.begin();
	lcd.setBacklight(255);
	lcd.clear();
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