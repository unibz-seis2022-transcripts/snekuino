#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "canvas.h"
#include "world.h"
#include "pixelhelper.h"
#include "gamemode.h"

#define WINDOW_X	100
#define WINDOW_Y	100

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	1024

int rows = 8;
int cols = 8;

bool aPressed = false;
bool dPressed = false;
bool sPressed = false;
bool wPressed = false;
bool enterPressed = false;

struct world* world;

void updateGamePixels(struct world* world) {
	clearPixels();

	if (world->foodBlinking) {
		for (int i = 0; i < world->foodAmount; i++) {
			canvasSetPixel(world->food[i].x, world->food[i].y, 0.5);
		}
	}

	for (int i = 0; i < world->obstacleAmount; i++) {
		canvasSetPixel(world->obstacle[i].x, world->obstacle[i].y, 0.25);
	}

	struct position* snakeBody = getBody(world->snake);
	for (int i = 1; i < world->snake->length; i++) {
		canvasSetPixel(snakeBody[i].x, snakeBody[i].y, 0.8);
	}

	canvasSetPixel(getHead(world->snake).x, getHead(world->snake).y, 1);
}

void cleanup(struct world* world)
{
	free(world->snake);
	free(world);
	canvasClose();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (canvasInit(WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, rows, cols))
	{
		printf("ERROR: init failed (invalid argument?)\n");
		return EXIT_FAILURE;
	}
	//int chosenMode = promptGamemodeDecision();

	switch (promptGamemodeDecision()) {
		case 1:
			world = createWorld(0, 1);
			break;
		case 2:
			world = createWorld(15, 2);
			break;
		default:
			world = createWorld(0, 1);
			break;
	}

	while (updateWorld(world) == 0 && canvasUpdate() == 0)
	{
		updateGamePixels(world);
		repaint();
	}

	cleanup(world);

	return EXIT_SUCCESS;
}