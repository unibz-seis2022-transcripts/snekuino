#ifndef __Buzzer_h__
#define __Buzzer_h__

class Buzzer {
	public:
		Buzzer(int pin);
		void playSound(unsigned int frequency, unsigned long duration = 0UL);
		
	private:
		int pin;
};

#endif