#ifndef __BuzzerTask_h__
#define __BuzzerTask_h__

#include "Buzzer.h"
#include "VibroMotor.h"
#include "Task.h"

class SensoryFeedbackTask: public Task {
	public:
		SensoryFeedbackTask(Buzzer* buzzer, VibroMotor* vibroMotor);
		void init(int period);
		void tick();

	private:
		Buzzer* buzzer;
		VibroMotor* vibroMotor;
};

#endif