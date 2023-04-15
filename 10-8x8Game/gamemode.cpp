#include "gamemode.h"
#include "snake.h"
#include "pixelhelper.h"
#include "canvas.h"
#include <stdlib.h>
#include "numbers.h"

extern bool aPressed;
extern bool enterPressed;
extern bool dPressed;
extern bool qPressed;

gameMode chosenGamemode;

position cursorOnePixels[] = {
	{ 1, 7 },
	{ 2, 7 },
	{ 3, 7 },
	{ 2, 6 },
};

position cursorTwoPixels[] = {
	{ 4, 7 },
	{ 5, 7 },
	{ 6, 7 },
	{ 5, 6 },
};
int cursorPixelsLength = sizeof(cursorOnePixels) / sizeof(cursorOnePixels[0]);

void updateGamemodePixels() { 
	clearPixels();

	drawNumber(12);

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
