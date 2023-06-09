#ifndef __snake_h__
#define __snake_h__

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

void initializeSnake(struct snake* snake);

void move(struct snake* snake);

void grow(struct snake* snake);

void changeDir(struct position newDir, struct snake* snake);

bool isKnotted(struct snake* snake);

#endif
