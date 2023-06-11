#include "GameTask.h"
#include <stdlib.h>
#include "game.h"
#include "world.h"
#include "snakeOutro.h"
#include "GameState.h"
#include "Gamemode.h"
#include "FeedbackState.h"
#include "Arduino.h"

extern struct game *game;
extern enum GAME_STATE gameState;
extern enum FEEDBACK_STATE feedbackState;

extern bool aPressed;
extern bool dPressed;

GameTask::GameTask() {
}

void GameTask::init(int period) {
	Task::init(period);
}

void GameTask::tick() {
	switch (gameState) {
		case CHOOSE_GAME_MODE:
			if (aPressed && game->gameMode != CLASSIC) {
				game->gameMode = CLASSIC;
				feedbackState = GAMEMODE_SELECT;
			};
			if (dPressed && game->gameMode != LABYRINTH) {
				game->gameMode = LABYRINTH;
				feedbackState = GAMEMODE_SELECT;
			};
			break;

		case PREPARE_GAME:
			initGame();
			gameState = IN_PROGRESS;
			break;

		case IN_PROGRESS:
			if (!gameStep(game)) {
				gameState = SET_UP_OUTRO;
			}
			break;

		case SET_UP_OUTRO:
			setUpOutro(game);
			gameState = OUTRO;
			break;

		case OUTRO:
			if (!outroStep(game)) {
				gameState = SCORE_PROMPT;
			}
			break;

		case SCORE_PROMPT:
			if (game->bestScore <= game->world->snake->length) {
				game->bestScore = game->world->snake->length;
				feedbackState = OUTRO_TUNE_BEST_SCORE;
			} else {
				feedbackState = OUTRO_TUNE;
			}
			break;
		}
}