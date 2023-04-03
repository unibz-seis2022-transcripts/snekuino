#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <stdbool.h>

extern bool aPressed;
extern bool sPressed;
extern bool dPressed;
extern bool wPressed;
extern bool qPressed;
extern bool enterPressed;

int canvasInit(int x, int y, int width, int height, int resolutionX, int resolutionY);
void canvasClose();

int canvasUpdate();
void repaint();

void canvasSetPixel(int x, int y, float value);
void canvasSetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);

#endif
