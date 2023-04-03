#ifndef __WORLD_H__
#define __WORLD_H__

#include "snake.h"

struct world {
	struct snake* snake;
	struct position* food;
	int foodAmount;
	struct position* obstacle;
	int obstacleAmount;
};

struct world* createWorld();
int updateWorld(world* world);

#endif
