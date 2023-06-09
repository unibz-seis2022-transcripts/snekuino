#ifndef __world_h__
#define __world_h__

#include "snake.h"

struct world {
	struct snake* snake;
	struct position food[5];
	int foodAmount;
	struct position obstacle[15];
	int obstacleAmount;
};

void initializeWorld(struct world* world, int obstacleNumber_, int foodNumber_);
bool updateWorld(world* world);

#endif
