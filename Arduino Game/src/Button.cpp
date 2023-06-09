#include "Button.h"
#include "Arduino.h"

Button::Button(int buttonPin) {
	this->pin = buttonPin;
	pinMode(this->pin, INPUT_PULLUP);
}

bool Button::pressed() {
	return digitalRead(this->pin) == HIGH;
}

int Button::getPin() {
	return this->pin;
}
