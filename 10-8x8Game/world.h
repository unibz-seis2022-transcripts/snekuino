#ifndef __WORLD_H__
#define __WORLD_H__

#include "snake.h"

struct world {
	struct snake* snake;
	struct position food;
};

struct position getNewFoodPos();
struct world* createWorld();
void makeStep(struct world* world);

#endif
