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
MenuEvent::Event buttonMapping[4] = {
	MenuEvent::back,
	MenuEvent::scrollPrevious,
	MenuEvent::scrollNext,
	MenuEvent::click
};

MenuItem printButton("Print values");

bool toggleTest = false;
uint8_t valueTest = 0;
float valueTestFloat = 1;
uint8_t ipTest[] = {192,168,0,1};
String stringTest = "Hello World!";


Menu menu{ "top",
	new MenuItem("MenuLibrary tester"),
	&printButton,
	new Menu( "Container",
		&MenuBack,
		new MenuItem("Hello"),
		new MenuItem("World")
	),
	new MenuToggle("Toggle:", &toggleTest),
	new MenuValue("Value:",
		new MenuValues<uint8_t>(&valueTest, 255),
		new MenuValues<float>(&valueTestFloat, 1, 0, 0.1)
	),
	new MenuIP("IP:", &ipTest[0], &ipTest[1], &ipTest[2], &ipTest[3]),
	new MenuString("String:", &stringTest)
};


MenuOutput* outputs[] = {
	new MenuOutputOlimex16x2(&lcd)
};


void printValues(const MenuOp*) {
	Serial.print(F("Toggle is now: "));
	Serial.println(toggleTest);

	Serial.print("Values are now: ");
	Serial.print(valueTest);
	Serial.print(", ");
	Serial.println(valueTestFloat);

	Serial.print("IP is now: ");
	Serial.print(ipTest[0]);
	Serial.print('.');
	Serial.print(ipTest[1]);
	Serial.print('.');
	Serial.print(ipTest[2]);
	Serial.print('.');
	Serial.println(ipTest[3]);

	Serial.print("String is now: ");
	Serial.println(stringTest);

	Serial.print("Free Ram:");
	Serial.println(freeRam());
}

void setup() {
	Serial.begin(9600);
	lcd.begin();
	lcd.setBacklight(255);
	lcd.clear();
	menu.setOutput(outputs,1);
	MenuBack.setTitle("User back text");
	printButton.setHandlerForEvent(printValues, MenuEvent::click);
}

void doButtons() {
	uint8_t buttons = lcd.readAllButtons();
	for (uint8_t i=0; i<4; i++) {
		uint8_t currentButton = (buttons>>i)&1;
		if (currentButton==1) { // 1 == not pressed
			buttonState[i] = false;
			return;
		} else {
			if (buttonState[i] == false) {
				buttonState[i] = true;
				menu.handleEvent(buttonMapping[i]);
			}
		}
	}
}

void loop() {
	doButtons();
	menu.draw();
}