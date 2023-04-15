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
#include "numbers.h"
#include "score.h"
#include "snakeOutro.h"

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

void printHelp() {
	printf("========== CONTROLS ==========\n");
	printf("=   w   -> move up           =\n");
	printf("=   s   -> move down         =\n");
	printf("=   a   -> move left         =\n");
	printf("=   d   -> move right        =\n");
	printf("=   q   -> quit game         =\n");
	printf("=         /quit app          =\n");
	printf("= enter -> skip animation    =\n");
	printf("=         /choose gamemode   =\n");
	printf("==============================\n");
}

void cleanup() {
	free(game->world->snake);
	free(game->world);
	free(game);
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	printHelp();
	if (canvasInit(WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, rows, cols))
	{
		printf("ERROR: init failed (invalid argument?)\n");
		return EXIT_FAILURE;
	}
	while (true) {

		enterPressed = false;

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

		setUpOutro(game);
		while (outroStep(game) && canvasUpdate() == 0) {
			updateGamePixels(game);
			repaint();
			if (enterPressed) {
				break;
			}
		}

		enterPressed = false;

		int score = game->world->snake->length-1;
		
		promptScore(score);

		cleanup();
	}


	return EXIT_SUCCESS;
}