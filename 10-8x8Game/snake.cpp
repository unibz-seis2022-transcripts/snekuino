#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

#define BASE_SPEED 2000
#define STARTING_POSITION { 0, 0 }

int rows = 0;
int cols = 0;

struct body* allocBody(struct position pos) {
	struct body* body = (struct body*)malloc(sizeof(struct body));
	if (body != NULL) {
		body->pos = pos;
		body->next = NULL;
	}
	return body;
}
struct snake* createSnake(int r, int c) {
	struct snake* snake = (struct snake*)malloc(sizeof(struct snake));
	if (snake != NULL) {
		snake->body = allocBody(STARTING_POSITION);
		snake->direction = { 1, 0 };
		snake->speed = BASE_SPEED;
	}
	rows = r;
	cols = c;
	return snake;
}

void move(struct snake* snake) {

}

void grow(struct snake* snake) {

}

void changeDir(struct position newDir, struct snake* snake) {

}

bool isKnotted(struct snake* snakes) {
	return false;
}

struct position getHead(struct snake* snake) {
	return { 0, 0 };
}

struct position* getBody(struct snake* snake) {
	return {};
}