#ifndef __Calibration_h__
#define __Calibration_h__

#include "Gyroscope.h"
#include "Buzzer.h"
#include "MD_MAX72xx.h"

void calibrate(Gyroscope* gyroscope, Buzzer* buzzer, MD_MAX72XX* display);

#endif
