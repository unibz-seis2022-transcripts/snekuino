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
#include "game.h"

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
bool qPressed = false;
bool enterPressed = false;

struct game* game;

void updateGamePixels(struct game* game) {
	clearPixels();

	if (game->foodBlinking) {
		for (int i = 0; i < game->world->foodAmount; i++) {
			canvasSetPixel(game->world->food[i].x, game->world->food[i].y, 0.5);
		}
	}

	for (int i = 0; i < game->world->obstacleAmount; i++) {
		canvasSetPixel(game->world->obstacle[i].x, game->world->obstacle[i].y, 0.25);
	}

	struct position* snakeBody = getBody(game->world->snake);
	for (int i = 1; i < game->world->snake->length; i++) {
		canvasSetPixel(snakeBody[i].x, snakeBody[i].y, 0.8);
	}

	canvasSetPixel(getHead(game->world->snake).x, getHead(game->world->snake).y, 1);
}

void cleanup()
{
	free(game->world->snake);
	free(game->world);
	free(game);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	if (canvasInit(WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, rows, cols))
	{
		printf("ERROR: init failed (invalid argument?)\n");
		return EXIT_FAILURE;
	}
	while (true) {

		game = initGame();

		if (qPressed) {
			break;
		}

		while (gameStep(game) == 0 && canvasUpdate() == 0) {
			updateGamePixels(game);
			repaint();
			if (qPressed) {
				break;
			}
		}

		enterPressed = false;
		qPressed = false;

		cleanup();
	}


	return EXIT_SUCCESS;
}