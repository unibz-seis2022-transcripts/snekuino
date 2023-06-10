#include "Buzzer.h"
#include "Arduino.h"

Buzzer::Buzzer(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Buzzer::playSound(unsigned int frequency, unsigned long duration){
	tone(this->pin, frequency, duration);
}