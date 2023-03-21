#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int rows = -1;
int cols = -1;

bool isPositionInSnake(struct position pos, struct snake* snake) {
	struct position* body = getBody(snake);

	for (int i = 0; i < snake->length; i++) {
		if (body[i].x == pos.x && body[i].y == pos.y) {
			return true;
		}
	}

	return false;
}

position getNewFood(struct snake* snake) {
	struct position pos = {};
	
	do {
		pos.x = rand() % rows;
		pos.y = rand() % rows;
	} while (isPositionInSnake(pos, snake));

	return pos;
}

void createWorld(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
	
	// initialize snake
	struct snake* snake = createSnake(rows, cols);

	// init food
	srand(time(NULL));
}

void makeStep(world* world) {
	// check for food collision
	// if so, grow snake and reposition food

	// move snake
	// check for knot
}
