#ifndef __game_h__
#define __game_h__

#include "Gamemode.h"
#include "snake.h"

struct game {
	struct world* world;
	enum GAME_MODE gameMode;
	int stepDelay;
	int blinkDelay;
	int bestScore;
	bool foodBlinking;
	struct position setDirection;
};

void initGame();

bool gameStep(struct game* game);

#endif