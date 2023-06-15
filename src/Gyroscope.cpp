#include "GY521.h"
#include "Gyroscope.h"
#include <Wire.h>

Gyroscope::Gyroscope(int address) {
  this->gyroscope = new GY521(address);
  Wire.begin();

  delay(100);

  while(this->gyroscope->wakeup() == false) {
    delay(1000);
  }
  this->gyroscope->setAccelSensitivity(2);  //  8g
  this->gyroscope->setGyroSensitivity(1);   //  500 degrees/s

  this->gyroscope->setThrottle();

  this->angleX = 0;
  this->angleY = 0;
  this->alpha  = 0.1;
}

float Gyroscope::getAngleX() {
  this->gyroscope->read();
  this->angleX = (this->alpha * this->gyroscope->getAngleX()) + (1 - this->alpha) * this->angleX;
  return this->angleX;
}

float Gyroscope::getAngleY() {
  this->gyroscope->read();
  this->angleY = (this->alpha * this->gyroscope->getAngleY()) + (1 - this->alpha) * this->angleY;
  return this->angleY;
}