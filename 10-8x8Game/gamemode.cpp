#include "gamemode.h"
#include "snake.h"
#include "pixelhelper.h"
#include "canvas.h"
#include <stdlib.h>

extern bool aPressed;
extern bool enterPressed;
extern bool dPressed;
extern bool qPressed;

gameMode chosenGamemode;

position numberOnePixels[] = {
		{ 1, 4 },
		{ 0, 3 },
		{ 1, 3 },
		{ 1, 2 },
		{ 1, 1 },
		{ 1, 0 },
};
int numberOnePixelsLength = sizeof(numberOnePixels) / sizeof(numberOnePixels[0]);

position numberTwoPixels[] = {
	{ 4, 4 },
	{ 5, 4 },
	{ 6, 3 },
	{ 5, 2 },
	{ 4, 1 },
	{ 4, 0 },
	{ 5, 0 },
	{ 6, 0 }
};
int numberTwoPixelsLength = sizeof(numberTwoPixels) / sizeof(numberTwoPixels[0]);

position cursorOnePixels[] = {
	{ 0, 7 },
	{ 1, 7 },
	{ 2, 7 },
	{ 1, 6 },
};
int cursorPixelsLength = sizeof(cursorOnePixels) / sizeof(cursorOnePixels[0]);

position cursorTwoPixels[] = {
	{ 4, 7 },
	{ 5, 7 },
	{ 6, 7 },
	{ 5, 6 },
};

void updateGamemodePixels() { 
	clearPixels();

	drawPixels(numberOnePixels, numberOnePixelsLength);
	drawPixels(numberTwoPixels, numberTwoPixelsLength);

	if (chosenGamemode == CLASSIC) {
		drawPixels(cursorOnePixels, cursorPixelsLength);
	}
	if (chosenGamemode == LABYRINTH) {
		drawPixels(cursorTwoPixels, cursorPixelsLength);
	}
}

gameMode promptGamemodeDecision()
{
	chosenGamemode = CLASSIC;

	while (!enterPressed && canvasUpdate() == 0)
	{
		if (aPressed) {
			chosenGamemode = CLASSIC;
		};
		if (dPressed) {
			chosenGamemode = LABYRINTH;
		};
		if (qPressed) {
			canvasClose();
			break;
		}
		updateGamemodePixels();
		repaint();
	}

	return chosenGamemode;
}
