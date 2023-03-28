#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern int rows;
extern int cols;

extern bool aPressed;
extern bool sPressed;
extern bool dPressed;
extern bool wPressed;

float delay = 0;
struct position setDirection = { 0, 0 };

bool isPositionInSnake(struct position pos, struct snake* snake) {
	struct position* body = getBody(snake);

	for (int i = 0; i < snake->length; i++) {
		if (body[i].x == pos.x && body[i].y == pos.y) {
			return true;
		}
	}
	return false;
}

bool snakeWillEat(struct world* world) {
	return 
		(world->food.x == getHead(world->snake).x + world->snake->direction.x)
		&&
		(world->food.y == getHead(world->snake).y + world->snake->direction.y);
}

void spawnNewFood(struct world* world) {
	int freeSpaces = (rows * cols) - world->snake->length;
	int newFoodPosition = rand() % freeSpaces+1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!isPositionInSnake({ i, j }, world->snake)) {
				newFoodPosition--;
			}

			if (newFoodPosition == 0) {
				world->food = { i, j };
				return;
			}
		}
	}
}

struct world* createWorld() {
	struct world* world = (struct world*)malloc(sizeof(struct world));
	if (world != NULL) {
		world->snake = createSnake();
	}
	spawnNewFood(world);

	return world;
}

struct position getUpdatedDirection(struct position currentSetDir, struct snake* snake) {
	struct position direciton = snake->direction;
	if (aPressed)
		if (snake->length == 1 || (currentSetDir.x != 1 && direciton.x != 1))
			return { -1, 0 };
	if (dPressed)
		if (snake->length == 1 || (currentSetDir.x != -1 && direciton.x != -1))
			return { 1, 0 };
	if (sPressed)
		if (snake->length == 1 || (currentSetDir.y != 1 && direciton.y != 1))
			return { 0, -1 };
	if (wPressed)
		if (snake->length == 1 || (currentSetDir.y != -1 && direciton.y != -1))
			return { 0, 1 };

	return currentSetDir;
}

void makeStep(world* world) {
	if (snakeWillEat(world)) {
		grow(world->snake);
		world->snake->speed--;
		spawnNewFood(world);
	}
	else {
		move(world->snake);
	}
}

int updateWorld(world* world) {
	if (isKnotted(world->snake)) {
		printf("YOU DIED");
		return 1;
	}
	setDirection = getUpdatedDirection(setDirection, world->snake);
	if (delay == world->snake->speed) {
		changeDir(setDirection, world->snake);
		makeStep(world);
		delay = 0;
	}
	delay++;
	return 0;
}
