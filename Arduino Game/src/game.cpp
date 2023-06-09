#include "game.h"
#include <stdlib.h>
#include "world.h"
#include "Arduino.h"

#define BLINK_DELAY 300;

extern bool aPressed;
extern bool sPressed;
extern bool dPressed;
extern bool wPressed;

extern struct game* game;

void initGame() {

	switch (game->gameMode) {
		case CLASSIC:
			initializeWorld(game->world, 0, 3);
			break;
		case LABYRINTH:
			initializeWorld(game->world, 15, 2);
			break;
		default:
			initializeWorld(game->world, 0, 1);
			break;
	}

	game->blinkDelay = 0;
	game->foodBlinking = true;
	game->stepDelay = 0;
	game->setDirection = { 0, 0 };
}

struct position getUpdatedDirection(struct position currentSetDir, struct snake* snake) {
	struct position direction = snake->direction;
	if (aPressed)
		if (snake->length == 1 || (currentSetDir.x != 1 && direction.x != 1))
			return { -1, 0 };
	if (dPressed)
		if (snake->length == 1 || (currentSetDir.x != -1 && direction.x != -1))
			return { 1, 0 };
	if (sPressed)
		if (snake->length == 1 || (currentSetDir.y != 1 && direction.y != 1))
			return { 0, -1 };
	if (wPressed)
		if (snake->length == 1 || (currentSetDir.y != -1 && direction.y != -1))
			return { 0, 1 };

	return currentSetDir;
}

bool gameStep(struct game* game) {
	game->setDirection = getUpdatedDirection(game->setDirection, game->world->snake);
	if (game->stepDelay <= 0) {
		changeDir(game->setDirection, game->world->snake);
		game->stepDelay = game->world->snake->speed;
		return updateWorld(game->world);
	}
	if (game->blinkDelay <= 0) {
		game->foodBlinking = !game->foodBlinking;
		game->blinkDelay = BLINK_DELAY;
	}
	game->blinkDelay-=10;
	game->stepDelay-=10;
	return true;
}