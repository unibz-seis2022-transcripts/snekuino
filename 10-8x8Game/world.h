#ifndef __WORLD_H__
#define __WORLD_H__

#include "snake.h"

struct world {
	struct snake* snake;
	struct position food;
};

struct position getNewFoodPos();
void createWorld(int rows, int columns);
void makeStep(struct world* world);

#endif
