#include "VibroMotor.h"
#include "Arduino.h"

VibroMotor::VibroMotor(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void VibroMotor::turnOn() {
	// digitalWrite(this->pin, HIGH); 
	digitalWrite(4, HIGH); 
}

void VibroMotor::turnOff() {
	// digitalWrite(this->pin, LOW); 
	digitalWrite(4, LOW); 
}