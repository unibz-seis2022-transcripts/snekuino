#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

struct snake* createSnake() {
	struct snake* snake = (struct snake*)malloc(sizeof(struct snake));
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