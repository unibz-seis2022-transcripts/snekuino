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

void addHead(struct snake* snake) {
	struct position oldHeadPosition = snake->body->pos;
	struct position direction		= snake->direction;
	struct position newHeadPosition = { (oldHeadPosition.x + direction.x + rows) % rows, (oldHeadPosition.y + direction.y + cols) % cols };
	struct body* newHead = allocBody(newHeadPosition);
	newHead->next = snake->body;
	snake->body = newHead;
	snake->length++;
}

void removeTail(struct snake* snake) {
	struct body* tmp = snake->body;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	free(tmp);
	snake->length--;
}

struct snake* createSnake(int _rows, int _cols) {
	struct snake* snake = (struct snake*)malloc(sizeof(struct snake));
	if (snake != NULL) {
		snake->body = allocBody(STARTING_POSITION);
		snake->direction = { 1, 0 };
		snake->speed = BASE_SPEED;
		snake->length = 1;
	}
	rows = _rows;
	cols = _cols;
	return snake;
}

void move(struct snake* snake) {
	grow(snake);
	removeTail(snake);
}

void grow(struct snake* snake) {
	addHead(snake);
}

void changeDir(struct position newDir, struct snake* snake) {
	snake->direction = newDir;
}

bool isKnotted(struct snake* snakes) {
	return false;
}

struct position getHead(struct snake* snake) {
	return snake->body->pos;
}

struct position* getBody(struct snake* snake) {
	struct position* bodyArray = (struct position*)malloc(snake->length * sizeof(struct position));
	struct body* tmp = snake->body;
	for (int i = 0; i < snake->length; i++, tmp = tmp->next) {
		bodyArray[i] = tmp->pos;
	}
	return bodyArray;
}