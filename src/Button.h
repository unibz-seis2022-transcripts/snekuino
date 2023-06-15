#ifndef __Button_h__
#define __Button_h__

class Button {

	public: 
		Button(int buttonPin);
		bool pressed();
		int getPin();

	private:
		int pin;

};

#endif
