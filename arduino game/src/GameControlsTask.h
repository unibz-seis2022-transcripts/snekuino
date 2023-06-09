#ifndef __GameControlsTaks_h__
#define __GameControlsTaks_h__

#include "Gyroscope.h"
#include "Button.h"
#include "Task.h"

class GameControlsTask: public Task {

	public:
		GameControlsTask(Gyroscope* gyroscope);
		void init(int period);
		void tick();

	private:
		Gyroscope* gyroscope;
};

#endif