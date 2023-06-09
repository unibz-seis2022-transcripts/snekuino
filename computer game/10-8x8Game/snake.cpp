#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

#define BASE_SPEED 200
#define STARTING_POSITION { 0, 0 }

extern int rows;
extern int cols;

void addHead(struct snake* snake) {
	struct position oldHeadPosition = snake->body[0];
	struct position direction = snake->direction;
	struct position newHeadPosition = { (oldHeadPosition.x + direction.x + rows) % rows, (oldHeadPosition.y + direction.y + cols) % cols };
	snake->length++;
	for (int i = snake->length - 1; i >= 0; i--) {
		snake->body[i] = snake->body[i - 1];
	}
	snake->body[0] = newHeadPosition;
}

void removeTail(struct snake* snake) {
	snake->body[snake->length] = { 0, 0 };
	snake->length--;
}

struct snake* createSnake() {
	struct snake* snake = (struct snake*)malloc(sizeof(struct snake));
	if (snake != NULL) {
		snake->body[0] = STARTING_POSITION;
		snake->direction = { 0, 0 };
		snake->speed = BASE_SPEED;
		snake->length = 1;
	}
	return snake;
}

void move(struct snake* snake) {
	addHead(snake);
	removeTail(snake);
}

void grow(struct snake* snake) {
	addHead(snake);
}

void changeDir(struct position newDir, struct snake* snake) {
	snake->direction = newDir;
}

bool isKnotted(struct snake* snake) {
	struct position head = snake->body[0];
	for (int i = 1; i < snake->length; i++) {
		if (head.x == snake->body[i].x && head.y == snake->body[i].y) {
			return true;
		}
	}
	return false;
}

struct position getHead(struct snake* snake) {
	return snake->body[0];
}

struct position* getBody(struct snake* snake) {
	return snake->body;
}
