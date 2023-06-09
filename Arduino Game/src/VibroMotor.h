#ifndef __VibroMotor_h__
#define __VibroMotor_h__

class VibroMotor {
	public:
		VibroMotor(int pin);
		void turnOn();
		void turnOff();
	
	private:
		int pin;
};

#endif