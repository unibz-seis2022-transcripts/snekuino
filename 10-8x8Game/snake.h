#ifndef __SNAKE_H__
#define __SNAKE_H__

struct position {
	int x;
	int y;
};

struct body {
	struct position pos;
	struct position* next;
};

struct snake {
	struct body* body;
	struct position direction;
	int speed;
};

struct snake* createSnake();

void move(struct snake* snake);

void grow(struct snake* snake);

void changeDir(struct position newDir, struct snake* snake);

bool isKnotted(struct snake* snakes);

struct position getHead(struct snake* snake);

struct position* getBody(struct snake* snake); //returns an array, but C is stupid, so is a pointer

#endif
