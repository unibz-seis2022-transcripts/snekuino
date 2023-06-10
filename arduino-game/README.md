# Snek Arduino Game

## Gameplay (logic + controls)

The game has two game modes: Mode 1 for the classic snake game, Mode 2 for a harder version that involves obstacles that the player needs to avoid. 

The green button is used for choosing the game mode and starting the game, the red button can be used to quit a running game.

The movement is controlled by tilting the device into different directions. If the snek dies, a final animation will be played, representing the total length of the snek, before the score is being displayed.

Every time the snek eats a food, the buzzer plays a tone. During the final animation the game case vibrates to indicate that the game is over. Upon displaying the score one of two melodies is played: A happy melody if a new highscore has been reached and a sad one if not.

## Hardware schematic (Fritzing)

The fritzing file can be found here: `schematics/snek-project.fzz`

![](img/fritzing.png)

## Hardware (Soldered version)

To make the game more usable and enjoyable we soldered our components to a prototyping breadboard which can be plugged on top of an Arduino, thus creating SnekShield™.

![](img/soldered-hardware-1.jpg)
![](img/soldered-hardware-2.jpg)
![](img/soldered-hardware-3.jpg)

## 3D case files

We designed and 3d-printed a case to hold the Arduino, the power supply (a 9V battery) and the SnekShield™. The case consists of three parts, the .stl files can be found in `schematics/3d-case/`. The different parts then need to be screwed together using

## Items we used

- Arduino Uno
- MPU 6050 Gyroscope
- MAX7219 serial interface for 8x8 LED Dot matrix
- BC337 Transistor
- Vibration motor
- Buzzer
- Two Buttons
- 1 kΩ resistor
 
## How to compile and upload the code to Arduino

