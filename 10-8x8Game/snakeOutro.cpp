#include "snakeOutro.h"
#include "canvas.h"
#include "pixelhelper.h"
#include "snake.h"
#include "game.h"
#include "world.h"

#define DELAY_SPEED 200

extern int rows;
extern int cols;

int boundaryRight = cols-1;
int boundaryTop = rows-1;
int boundaryLeft = 0;
int boundaryBottom = 0;

int maxSnekLength = 0;
int delay = DELAY_SPEED;

void updateSnekPixels(world* world) {
	clearPixels();
	
}

void changeDir(struct snake* snake) {
	if (snake->body[0].pos.x + snake->direction.x-)
}

int outroStep(world* world) {
	if (delay <= 0) {
		changeDir(world->snake);
		game->stepDelay = game->world->snake->speed;
		return updateWorld(game->world);
	}
	game->stepDelay -= 10;
	return 0;
}

void promptSnakeOutro(game* game) {
	maxSnekLength = game->world->snake->length;
	struct world* world = createWorld(0, 0);
	while (outroStep(world) == 0 && canvasUpdate() == 0) {
		updateSnekPixels(world);
		if (delay <= 0) {
			delay = DELAY_SPEED;
		}
		if (qPressed) {
			canvasClose();
			break;
		}
		repaint();
		delay-=10;
	}
}
