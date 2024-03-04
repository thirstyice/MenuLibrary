#include <Arduino.h>


#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

#include <Menu.h>
#include <MenuToggle.h>
#include <MenuValue.h>
#include <MenuOutput/PCF8574.h>

#include <AceButton.h>
#include <RotaryEncoder.h>


LiquidCrystal_PCF8574 lcd(0x27);

RotaryEncoder encoder(3,2,RotaryEncoder::LatchMode::FOUR3);
long lastEncPosition = 0;
ace_button::AceButton button(4);

MenuItem printButton("Print variable values");

bool toggleTest = false;
uint8_t valueTest = 0;


static Menu<4> menu{ "top",
	new MenuItem("MenuLibrary tester"),
	new Menu<2>( "Container",
		new MenuItem("Hello"),
		new MenuItem("World")
	),
	new MenuToggle("Toggle:", &toggleTest),
	new MenuValue<uint8_t>("Value:", &valueTest, 255)
};

MenuOutputPCF8574 lcdOut(&lcd, 20, 4);

void buttonEventHandler(ace_button::AceButton*, uint8_t eventType, uint8_t) {
	switch (eventType) {
		case ace_button::AceButton::kEventClicked:
			menu.handleEvent(MenuItem::click);
			break;
		case ace_button::AceButton::kEventLongPressed:
			menu.handleEvent(MenuItem::exit);
			break;
	}
}

void encoderInterrupt() {
	encoder.tick();
}

void printValues(const MenuOp*) {
	Serial.print(F("Toggle is now: "));
	Serial.println(toggleTest);
	Serial.print("Value is now:");
	Serial.println(valueTest);
}

void setup() {
	Serial.begin(9600);

	menu.setOutput(&lcdOut,1);
	lcd.begin(20,4);
	lcd.setBacklight(255);
	lcd.clear();
	lcd.home();
	printButton.setHandlerForEvent(printValues, MenuOp::click);

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
	MenuItem::Event event = MenuItem::scrollNext;
	if (encPosition < 0) {
		event = MenuItem::scrollPrevious;
		encPosition *= -1;
	}
	while (encPosition > 0) {
		menu.handleEvent(event);
		encPosition --;
	}
	button.check();
	menu.draw();
}