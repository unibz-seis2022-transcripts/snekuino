#include "Arduino.h"
#include "SensoryFeedbackTask.h"
#include "FeedbackState.h"
#include "Notes.h"

extern enum FEEDBACK_STATE feedbackState;

int delayTune = 0;

SensoryFeedbackTask::SensoryFeedbackTask(Buzzer* buzzer, VibroMotor* vibromotor) {
	this->buzzer     = buzzer;
	this->vibroMotor = vibroMotor;
}

void SensoryFeedbackTask::init(int period) {
	Task::init(period);
}

void SensoryFeedbackTask::tick() {
	switch (feedbackState) {
		case OFF:
			delayTune = 0;
			this->vibroMotor->turnOff();
			break;
		case FOOD_EATEN:
			this->buzzer->playSound(3000, 50);
			feedbackState = OFF;
			break;
		case GAMEMODE_SELECT:
			this->buzzer->playSound(440, 50);
			feedbackState = OFF;
			break;
		case ENTER:
			this->buzzer->playSound(3000, 50);
			feedbackState = OFF;
			break;
		case QUIT:
			this->buzzer->playSound(3000, 50);
			feedbackState = OFF;
			break;
		case COLLISION:
			this->vibroMotor->turnOn();
			break;
    case OUTRO_TUNE:
			this->vibroMotor->turnOff();
			if (delayTune < 200) {
        this->buzzer->playSound(NOTE_A_FLAT, 200);
			} else if (delayTune < 400) {
	      this->buzzer->playSound(NOTE_G, 200);
			} else if (delayTune < 600) {
        this->buzzer->playSound(NOTE_G_FLAT, 200);
			} else if (delayTune < 800) {
        this->buzzer->playSound(NOTE_F, 200);
				feedbackState = OFF;
			}
			delayTune += 10;
      break;
    case OUTRO_TUNE_BEST_SCORE:
		this->vibroMotor->turnOff();
		if (delayTune < 100) {
			this->buzzer->playSound(NOTE_A, 100);
		} else if (delayTune < 200) {
			this->buzzer->playSound(NOTE_B, 100);
		} else if (delayTune < 300) {
				this->buzzer->playSound(NOTE_C_SHARP, 100);
		} else if (delayTune < 500) {
			this->buzzer->playSound(NOTE_E, 200);
		} else if (delayTune < 580) {
			this->buzzer->playSound(NOTE_C_SHARP, 80);
		} else if (delayTune < 780) {
			this->buzzer->playSound(NOTE_E, 200);
			feedbackState = OFF;
		}
		delayTune += 10;
		feedbackState = OFF;
      	break;
	}
}