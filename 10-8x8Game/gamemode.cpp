#include "gamemode.h"
#include "snake.h"
#include "pixelhelper.h"
#include "canvas.h"
#include <stdlib.h>

extern bool aPressed;
extern bool enterPressed;
extern bool dPressed;

struct gamemodeState {
	int cursorPosition;
	int chosenGamemode;
};

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

void updateGamemodePixels(struct gamemodeState* state) { 
	clearPixels();

	drawPixels(numberOnePixels, numberOnePixelsLength);
	drawPixels(numberTwoPixels, numberTwoPixelsLength);

	if (state->cursorPosition == 1) {
		drawPixels(cursorOnePixels, cursorPixelsLength);
	}
	if (state->cursorPosition == 2) {
		drawPixels(cursorTwoPixels, cursorPixelsLength);
	}
}

int updateGamemodeState(gamemodeState* state) {
	if (aPressed) {
		state->cursorPosition = 1;
	};
	if (dPressed) {
		state->cursorPosition = 2;
	};
	if (enterPressed) {
		state->chosenGamemode = state->cursorPosition;
		return 1;
	};

	return 0;
}

int promptGamemodeDecision()
{
	struct gamemodeState* state = (struct gamemodeState*)malloc(sizeof(struct gamemodeState));
	state->cursorPosition = 1;

	while (updateGamemodeState(state) == 0 && canvasUpdate() == 0)
	{
		updateGamemodePixels(state);
		repaint();
	}

	return state->chosenGamemode;
}
