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

struct gamemodeState {
	int cursorPosition;
	int chosenGamemode;
};

position cursorOnePixels[] = {
	{ 0, 7 },
	{ 1, 7 },
	{ 2, 7 },
	{ 1, 6 },
};

position cursorTwoPixels[] = {
	{ 4, 7 },
	{ 5, 7 },
	{ 6, 7 },
	{ 5, 6 },
};
int cursorPixelsLength = sizeof(cursorOnePixels) / sizeof(cursorOnePixels[0]);

void updateGamemodePixels(struct gamemodeState* state) { 
	clearPixels();

	drawNumber(12);

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
		if (qPressed) {
			canvasClose();
			break;
		}
		updateGamemodePixels(state);
		repaint();
	}

	return state->chosenGamemode;
}
