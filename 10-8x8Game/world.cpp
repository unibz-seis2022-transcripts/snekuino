#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FOOD_AMOUNT 2.0
#define OBSTACLE_AMOUNT 15.0

extern int rows;
extern int cols;

extern bool aPressed;
extern bool sPressed;
extern bool dPressed;
extern bool wPressed;

float delay = 0;
int growDelay = 0;
struct position setDirection = { 0, 0 };

bool isPositionOccupied(struct position pos, struct position* occupied, int occupiedLenght) {
	for (int i = 0; i < occupiedLenght; i++) {
		if (occupied[i].x == pos.x && occupied[i].y == pos.y) {
			return true;
		}
	}
	return false;
}

int snakeWillEat(struct world* world) {
	for (int i = 0; i < world->foodAmount; i++) {
		if ((world->food[i].x == getHead(world->snake).x + world->snake->direction.x)
			&&
		    (world->food[i].y == getHead(world->snake).y + world->snake->direction.y)
		) {
			return i;
		}
	}
	return -1;
}

void spawnNewEntity(struct world* world, int freeSpaces, struct position* entityArray, int index) {
	int newEntityPosition = rand() % freeSpaces+1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!isPositionOccupied({ i, j }, getBody(world->snake), world->snake->length)
			 && !isPositionOccupied({i, j}, world->obstacle, world->obstacleAmount)
			 && !isPositionOccupied({ i, j }, world->food, world->foodAmount)
			) {
				newEntityPosition--;
			}

			if (newEntityPosition == 0) {
				entityArray[index] = {i, j};
				return;
			}
		}
	}
}

struct world* createWorld() {
	struct world* world = (struct world*)malloc(sizeof(struct world));
	if (world != NULL) {
		world->snake = createSnake();
		world->foodAmount = FOOD_AMOUNT;
		world->obstacleAmount = OBSTACLE_AMOUNT;
		world->food = (struct position*)malloc(sizeof(struct position) * (world->foodAmount));
		world->obstacle = (struct position*)malloc(sizeof(struct position) * (world->obstacleAmount));
		
		for (int i = 0; i < world->obstacleAmount; i++) {
			spawnNewEntity(world, ((rows * cols) - world->snake->length - i), world->obstacle, i);
		}

		for (int i = 0; i < world->foodAmount; i++) {
			spawnNewEntity(world, ((rows * cols) - world->snake->length - world->obstacleAmount - i), world->food, i);
		}
	}

	return world;
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

void makeStep(world* world) {
	int eatenFoodIndex = snakeWillEat(world);
	if (eatenFoodIndex != -1) {
		grow(world->snake);
		world->snake->speed -= 5;
		spawnNewEntity(world, ((rows * cols) - world->snake->length - world->obstacleAmount - world->foodAmount), world->food, eatenFoodIndex);
	}
	else {
		move(world->snake);
	}
}

bool isCrushed(world* world) {
	for (int i = 0; i < world->obstacleAmount; i++) {
		if (isPositionOccupied(world->obstacle[i], getBody(world->snake), world->snake->length)) {
			return true;
		}
	}
	return false;
}

int updateWorld(world* world) {
	if (isKnotted(world->snake) || isCrushed(world)) {
		printf("YOU DIED");
		return 1;
	}
	setDirection = getUpdatedDirection(setDirection, world->snake);
	if (delay <= 0) {
		changeDir(setDirection, world->snake);
		makeStep(world);
		delay = world->snake->speed;
	}
	delay-=10;
	return 0;
}
