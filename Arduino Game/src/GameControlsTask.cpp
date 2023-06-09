#include "GameControlsTask.h"
#include "game.h"
#include "world.h"
#include "snake.h"
#include "GameState.h"

#define SENSITIVITY 8
#define MAX_ANGLE 35
#define MAX_SPEED 100
#define MIN_SPEED 1000

extern bool aPressed;
extern bool dPressed;
extern bool sPressed;
extern bool wPressed;

extern struct game* game;
extern enum GAME_STATE gameState;

GameControlsTask::GameControlsTask(Gyroscope* gyroscope) {
  this->gyroscope = gyroscope;
}

void GameControlsTask::init(int period) {
  Task::init(period);
}

void GameControlsTask::tick() {
  aPressed = false;
  dPressed = false;
  sPressed = false;
  wPressed = false;

  int angleX = this->gyroscope->getAngleX();
  int angleY = this->gyroscope->getAngleY();

  int speed = game->world->snake->speed; 

  if (angleX > SENSITIVITY) { //TODO: find optimal value
    aPressed = true;
	speed = map(min(angleX, MAX_ANGLE), 0, MAX_ANGLE, MIN_SPEED, MAX_SPEED);
  } else if (angleX < -SENSITIVITY) {
	speed = map(max(angleX, -MAX_ANGLE), -MAX_ANGLE, 0, MAX_SPEED, MIN_SPEED);
    dPressed = true;
  }

  if (angleY > SENSITIVITY) {
	speed = map(min(angleY, MAX_ANGLE), 0, MAX_ANGLE, MIN_SPEED, MAX_SPEED);
    wPressed = true;
  } else if (angleY < -SENSITIVITY) {
	speed = map(max(angleY, -MAX_ANGLE), -MAX_ANGLE, 0, MAX_SPEED, MIN_SPEED);
    sPressed = true;
  }

  if (gameState == IN_PROGRESS) {
	game->world->snake->speed = speed;
  }
}