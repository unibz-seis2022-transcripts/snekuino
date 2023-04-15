#include "snakeOutro.h"
#include "canvas.h"
#include "pixelhelper.h"
#include "snake.h"
#include "world.h"
#include <stdlib.h>

extern int rows;
extern int cols;

int boundaryRight;
int boundaryTop;
int boundaryLeft;
int boundaryBottom;

int maxLength;
int speed;

void setUpOutro(game* game) {
	boundaryRight = cols - 1;
	boundaryTop = rows - 1;
	boundaryLeft = -1;
	boundaryBottom = 0;

	game->world->obstacleAmount = 0;
	game->world->obstacle = NULL;
	game->world->foodAmount = 0;
	game->world->food = NULL;
	maxLength = game->world->snake->length;
	speed = game->world->snake->speed;
	game->stepDelay = speed;
	game->world->snake = createSnake();
	game->world->snake->direction = { 1, 0 };
}

bool outroStep(game* game) {
	if (game->stepDelay <= 0) {
		struct position head = getHead(game->world->snake);
		
		if (head.x == boundaryRight && head.y == boundaryBottom) {
			game->world->snake->direction = { 0, 1 };
			boundaryLeft++;
		}
		if (head.x == boundaryRight && head.y == boundaryTop) {
			game->world->snake->direction = { -1, 0 };
			boundaryBottom++;
		}
		if (head.x == boundaryLeft && head.y == boundaryTop) {
			game->world->snake->direction = { 0, -1 };
			boundaryRight--;
		}
		if (head.x == boundaryLeft && head.y == boundaryBottom) {
			game->world->snake->direction = { 1, 0 };
			boundaryTop--;
		}

		grow(game->world->snake);
		game->stepDelay = speed;
	}

	game->stepDelay -= 10;

	//return gameStep(game, true) && (game->world->snake->length == maxLength);
	return game->world->snake->length <= maxLength;
}
