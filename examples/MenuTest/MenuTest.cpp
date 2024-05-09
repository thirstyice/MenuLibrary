#include <Arduino.h>

#include <MenuLibrary.h>

#include <MenuOutput/PCF8574.h>

#include <AceButton.h>
#include <RotaryEncoder.h>

int freeRam () {
	extern int __heap_start, *__brkval; 
	int v; 
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

LiquidCrystal_PCF8574 lcd(0x27);

RotaryEncoder encoder(3,2,RotaryEncoder::LatchMode::FOUR3);
long lastEncPosition = 0;
ace_button::AceButton button(4);

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

MenuOutputPCF8574 lcdOut(&lcd, 20, 4);

void buttonEventHandler(ace_button::AceButton*, uint8_t eventType, uint8_t) {
	switch (eventType) {
		case ace_button::AceButton::kEventClicked:
			menu.handleEvent(MenuEvent::click);
			break;
		case ace_button::AceButton::kEventLongPressed:
			menu.handleEvent(MenuEvent::back);
			break;
	}
}

void encoderInterrupt() {
	encoder.tick();
}

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
	lcd.begin(20,4);
	lcd.setBacklight(255);
	lcd.clear();
	lcd.home();
	menu.setOutput(&lcdOut,1);
	MenuBack.setTitle("User back text");
	printButton.setHandlerForEvent(printValues, MenuEvent::click);

	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);

	ace_button::ButtonConfig* buttonConfig = button.getButtonConfig();
	buttonConfig->setEventHandler(buttonEventHandler);
	buttonConfig->setFeature(ace_button::ButtonConfig::kFeatureClick);
	buttonConfig->setFeature(ace_button::ButtonConfig::kFeatureLongPress);

	attachInterrupt(digitalPinToInterrupt(2), encoderInterrupt, CHANGE);
	attachInterrupt(digitalPinToInterrupt(3), encoderInterrupt, CHANGE);
}

void loop() {
	encoder.tick();
	long encPosition = encoder.getPosition() - lastEncPosition;
	
	lastEncPosition = encoder.getPosition();
	MenuEvent::Event event = MenuEvent::scrollNext;
	if (encPosition < 0) {
		event = MenuEvent::scrollPrevious;
		encPosition *= -1;
	}
	while (encPosition > 0) {
		menu.handleEvent(event);
		encPosition --;
	}
	button.check();
	menu.draw();
}