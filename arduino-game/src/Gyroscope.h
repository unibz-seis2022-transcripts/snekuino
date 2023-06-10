#ifndef __Gyroscope_h__
#define __Gyroscope_h__

#include "GY521.h"

class Gyroscope {
  public:
    Gyroscope(int address);
    float getAngleX();
    float getAngleY();

  private:
    GY521* gyroscope;
    float   angleX;
    float   angleY;
    float alpha;
};

#endif