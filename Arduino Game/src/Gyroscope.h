#ifndef __Gyroscope_h__
#define __Gyroscope_h__

#include "GY521.h"

class Gyroscope {
  public:
    Gyroscope(int address);
    int getAngleX();
    int getAngleY();

  private:
    GY521* gyroscope;
    int   angleX;
    int   angleY;
    float alpha;
};

#endif