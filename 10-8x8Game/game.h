#pragma once
#include "gamemode.h"
#include "snake.h"

struct game {
	struct world* world;
	enum gameMode gameMode;
	int stepDelay;
	int blinkDelay;
	bool foodBlinking;
	struct position setDirection;
	//int delay;
};

struct game* initGame();

int gameStep(struct game* game);