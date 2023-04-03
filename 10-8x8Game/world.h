#ifndef __WORLD_H__
#define __WORLD_H__

#include "snake.h"

struct world {
	struct snake* snake;
	struct position* food;
	int foodAmount;
	bool foodBlinking;
	struct position* obstacle;
	int obstacleAmount;
};

struct world* createWorld(int obstacleNumber_, int foodNumber_);
int updateWorld(world* world);

#endif
