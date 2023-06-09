#ifndef __ManageInterrupt_h__
#define __ManageInterrupt_h__

#include "GameState.h"
#include "FeedbackState.h"
#include "Arduino.h"

extern enum GAME_STATE gameState;
extern enum FEEDBACK_STATE feedbackState;

class ManageInterrupt {
	public:
		static void EnterPressed() {
	  		feedbackState = OFF;
			if (gameState == CHOOSE_GAME_MODE) {
				gameState = PREPARE_GAME;
				feedbackState = ENTER;
			}
			// if (gameState == OUTRO) {
			// 	gameState = SCORE_PROMPT;
			// }
			// if (gameState == SCORE_PROMPT) {
			// 	gameState = CHOOSE_GAME_MODE;
			// }
		}

	static void QuitPressed() {
		if (gameState == IN_PROGRESS) {
			gameState = SET_UP_OUTRO;
			feedbackState = QUIT;
		}
	}
};

#endif