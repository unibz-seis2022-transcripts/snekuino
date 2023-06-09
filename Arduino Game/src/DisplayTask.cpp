#include "DisplayTask.h"
#include "game.h"
#include "world.h"
#include "GameState.h"
#include "Gamemode.h"

#define SCORE_SHOW_DELAY 1000

extern struct game *game;
extern enum GAME_STATE gameState;

int scoreDelay = SCORE_SHOW_DELAY;

enum ALTERNATE_SHOW {
	SNAKE,
	FOOD,
	OBSTACLE
};

enum ALTERNATE_SHOW alternate = SNAKE;

struct position cursorOnePixels[] = { {1, 7}, {2, 7}, {3, 7}, {2, 6}};

struct position cursorTwoPixels[] = { {4, 7}, {5, 7}, {6, 7}, {5, 6}};

int cursorPixelsLength = 4;

struct position numberOnePixels[] = { {2, 4}, {1, 3}, {2, 3}, {2, 2}, {2, 1}, {2, 0}};

struct position numberTwoPixels[] = { {0, 4}, {1, 4}, {2, 3}, {1, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}};

struct position numberThreePixels[] = { {0, 4}, {1, 4}, {2, 4}, {2, 3}, {1, 2}, {2, 1}, {1, 0}, {0, 0}};

struct position numberFourPixels[] = { {2, 4}, {1, 3}, {0, 2}, {0, 1}, {1, 1}, {2, 1}, {2, 0}};

struct position numberFivePixels[] = { {0, 0}, {1, 0}, {2, 1}, {1, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}};

struct position numberSixPixels[] = { {2, 4}, {1, 4}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {1, 2}};

struct position numberSevenPixels[] = { {0, 4}, {1, 4}, {2, 4}, {2, 3}, {1, 2}, {1, 1}, {1, 0}};

struct position numberEightPixels[] = { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {2, 3}, {0, 4}, {1, 4}, {2, 4}};

struct position numberNinePixels[] = { {0, 0}, {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}, {0, 3}, {2, 3}, {0, 4}, {1, 4}, {2, 4}};

struct position numberZeroPixels[] = { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {2, 1}, {0, 2}, {2, 2}, {0, 3}, {2, 3}, {0, 4}, {1, 4}, {2, 4}};

struct position *digitPixelArrays[] = {
	numberZeroPixels,
	numberOnePixels,
	numberTwoPixels,
	numberThreePixels,
	numberFourPixels,
	numberFivePixels,
	numberSixPixels,
	numberSevenPixels,
	numberEightPixels,
	numberNinePixels,
};

int lengths[] = { 12, 6, 8, 8, 7, 8, 12, 7, 13, 12 };

struct position *translatePixels(struct position *pixels, int lengthPixels, int translateX, int translateY) {
	struct position* translatedPositions = new position[lengthPixels];
	for (int i = 0; i < lengthPixels; i++) {
		translatedPositions[i] = {pixels[i].x + translateX, pixels[i].y + translateY};
	}
	return translatedPositions;
};

DisplayTask::DisplayTask(MD_MAX72XX *display) {
	this->display = display;
}

void DisplayTask::init(int period) {
	Task::init(period);
	this->display->begin();
}

void DisplayTask::displayFood(struct position* food, int foodAmount, bool foodBlinking) {
	this->display->control(this->display->INTENSITY, MAX_INTENSITY/4);

	if (foodBlinking) {
		for (int i = 0; i < foodAmount; i++) {
			this->display->setPoint(food[i].y, food[i].x, true);
		}
	}
}

void DisplayTask::displayObstacles(struct position* obstacles, int obstacleAmount) {
	this->display->control(this->display->INTENSITY, 0);

	for (int i = 0; i < obstacleAmount; i++) {
		this->display->setPoint(obstacles[i].y, obstacles[i].x, true);
	}
}

void DisplayTask::displaySnake(struct snake* snake) {
	this->display->control(this->display->INTENSITY, MAX_INTENSITY);

	for (int i = 0; i < snake->length; i++) {
		this->display->setPoint(snake->body[i].y, snake->body[i].x, true);
	}
}

void DisplayTask::drawPixels(struct position *pixels, int length, int translateX, int translateY) {
	this->display->control(this->display->INTENSITY, MAX_INTENSITY);
	for (int i = 0; i < length; i++) {
		struct position pixel = pixels[i];
		this->display->setPoint(pixel.y + translateY, pixel.x + translateX, true);
	}
}

void DisplayTask::drawDigit(int value, int translateX, int translateY) {
	int digit = value % 10;
	struct position *pixels = digitPixelArrays[digit];
	int lengthPixels = lengths[digit];

	this->drawPixels(pixels, lengthPixels, translateX, translateY);
}

void DisplayTask::drawNumber(int value, int translateY) {
	int twoDigitValue = value % 100;
	int leftDigit = twoDigitValue / 10;
	int rightDigit = twoDigitValue % 10;

	int translateXLeft = 0;
	int translateXRight = 4;
	drawDigit(leftDigit, translateXLeft, translateY);
	drawDigit(rightDigit, translateXRight, translateY);
}

void DisplayTask::tick() {
	switch (gameState) {
	case CHOOSE_GAME_MODE:
		this->display->clear();

		drawNumber(12);

		if (game->gameMode == CLASSIC) {
			this->drawPixels(cursorOnePixels, cursorPixelsLength);
		}
		if (game->gameMode == LABYRINTH) {
			this->drawPixels(cursorTwoPixels, cursorPixelsLength);
		}
		break;
	
	case PREPARE_GAME:
		this->display->clear();
		break;
	
	case IN_PROGRESS:
		this->display->clear();
		switch (alternate) {
			case SNAKE:
				this->displaySnake(game->world->snake);
				alternate = FOOD;
				break;
			case FOOD:
				this->displayFood(game->world->food, game->world->foodAmount, game->foodBlinking);
				alternate = OBSTACLE;
				break;
			case OBSTACLE:
				this->displayObstacles(game->world->obstacle, game->world->obstacleAmount);
				alternate = SNAKE;
				break;
		}
		break;

	case SET_UP_OUTRO:
		this->display->clear();
		break; 

	case OUTRO:
		this->display->clear();
		this->displaySnake(game->world->snake);
		break;

	case SCORE_PROMPT:
		this->display->clear();
		drawNumber(game->world->snake->length - 1, 1);
		scoreDelay -= 5;
		if (scoreDelay <= 0) {
			scoreDelay = SCORE_SHOW_DELAY;
			gameState  = CHOOSE_GAME_MODE;
		}
		break;
	}
}