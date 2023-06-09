#ifndef __GameTask_h__
#define __GameTask_h__

#include "Task.h"

class GameTask: public Task {
  public:
    GameTask();
    void init(int period);
	void tick();

  private:
	
    
};

#endif