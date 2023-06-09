#include "world.h"
#include "game.h"
#include "Arduino.h"
#include "FeedbackState.h"

#define FOOD_AMOUNT 2.0
#define OBSTACLE_AMOUNT 15.0

extern int rows;
extern int cols;

extern struct game* game;
extern enum FEEDBACK_STATE feedbackState;

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
		if ((world->food[i].x == (world->snake->body[0].x + world->snake->direction.x + rows) % rows)
			&&
			(world->food[i].y == (world->snake->body[0].y + world->snake->direction.y + cols) % cols)
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
			if (!isPositionOccupied({ i, j }, world->snake->body, world->snake->length)
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

void initializeWorld(struct world* world, int obstacleNumber_, int foodNumber_) {
	initializeSnake(world->snake);
	world->foodAmount = foodNumber_;
	world->obstacleAmount = obstacleNumber_;
	
	for (int i = 0; i < world->obstacleAmount; i++) {
		spawnNewEntity(world, ((rows * cols) - world->snake->length - i), world->obstacle, i);
	}

	for (int i = 0; i < world->foodAmount; i++) {
		spawnNewEntity(world, ((rows * cols) - world->snake->length - world->obstacleAmount - i), world->food, i);
	}
}

void makeStep(world* world) {
	int eatenFoodIndex = snakeWillEat(world);
	if (eatenFoodIndex != -1) {
		grow(world->snake);
		// world->snake->speed -= 5;
		spawnNewEntity(world, ((rows * cols) - world->snake->length - world->obstacleAmount - world->foodAmount), world->food, eatenFoodIndex);
		feedbackState = FOOD_EATEN;
	}
	else {
		move(world->snake);
	}
}

bool isCrushed(world* world) {
	for (int i = 0; i < world->obstacleAmount; i++) {
		if (isPositionOccupied(world->obstacle[i], world->snake->body, world->snake->length)) {
			return true;
		}
	}
	return false;
}

bool updateWorld(world* world) {
	if (isKnotted(world->snake) || isCrushed(world)) {
		feedbackState = COLLISION;
		return false;
	}
	makeStep(world);
	return true;
}
