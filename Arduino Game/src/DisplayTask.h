#ifndef __DisplayTask_h__
#define __DisplayTask_h__

#include <MD_MAX72xx.h> 
#include "Task.h"
#include "snake.h"
#include "game.h"

class DisplayTask: public Task {

  public:
    DisplayTask(MD_MAX72XX* display);
	void init(int period);
	void tick();

  private:
  	void displaySnake(struct snake* snake);
  	void displayFood(struct position* food, int foodAmount, bool foodBlinking);
	void displayObstacles(struct position* obstacles, int obstacleAmount);
	void drawPixels(struct position* pixels, int length, int translateX = 0, int translateY = 0);
	void drawDigit(int value, int translateX, int translateY);
	void drawNumber(int value, int translateY = 0);
    MD_MAX72XX* display;

};

#endif