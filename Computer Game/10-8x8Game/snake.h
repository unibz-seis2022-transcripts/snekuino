#ifndef __SNAKE_H__
#define __SNAKE_H__

struct position {
	int x;
	int y;
};

struct snake {
	struct position body[64];
	struct position direction;
	float speed;
	int length;
};

struct snake* createSnake();

void move(struct snake* snake);

void grow(struct snake* snake);

void changeDir(struct position newDir, struct snake* snake);

bool isKnotted(struct snake* snake);

struct position getHead(struct snake* snake);

struct position* getBody(struct snake* snake); //returns an array, but C is stupid, so is a pointer

#endif
