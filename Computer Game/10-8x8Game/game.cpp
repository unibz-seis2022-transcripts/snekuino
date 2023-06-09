#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "pixelhelper.h"
#include "gamemode.h"
#include "world.h"

#define BLINK_DELAY 300;

extern bool aPressed;
extern bool sPressed;
extern bool dPressed;
extern bool wPressed;

struct game* initGame() {

	struct game* game = (struct game*)malloc(sizeof(struct game));
	game->gameMode = promptGamemodeDecision();

	switch (game->gameMode) {
		case CLASSIC:
			game->world = createWorld(0, 1);
			break;
		case LABYRINTH:
			game->world = createWorld(15, 2);
			break;
		default:
			game->world = createWorld(0, 1);
			break;
	}

	game->blinkDelay = 0;
	game->foodBlinking = true;
	game->stepDelay = 0;
	game->setDirection = { 0, 0 };

	return game;
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

int gameStep(struct game* game) {
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
	game->blinkDelay -= 10;
	game->stepDelay-=10;
	return 0;
}