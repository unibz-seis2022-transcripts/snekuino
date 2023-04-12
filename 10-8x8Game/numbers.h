#pragma once
#include "snake.h"

position numberOnePixels[];
position numberTwoPixels[];
position numberThreePixels[];
position numberFourPixels[];
position numberFivePixels[];
position numberSixPixels[];
position numberSevenPixels[];
position numberEightPixels[];
position numberNinePixels[];
position numberZeroPixels[];

position* digitPixelArrays[];

void drawDigit(int value, int translateX, int translateY);
void drawNumber(int value, int translateY = 0);
