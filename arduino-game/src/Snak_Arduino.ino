#include <EnableInterrupt.h>
#include <MD_MAX72xx.h> 
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "world.h"

#include "Gyroscope.h"
#include "Button.h"
#include "Buzzer.h"
#include "VibroMotor.h"
#include "Calibration.h"
#include "ManageInterrupt.h"
#include "Scheduler.h"
#include "Task.h"
#include "GameControlsTask.h"
#include "DisplayTask.h"
#include "SensoryFeedbackTask.h"
#include "GameTask.h"
#include "GameState.h"
#include "FeedbackState.h"

#define HARDWARE_TYPE MD_MAX72XX::DR0CR1RR0_HW
#define MAX_DEVICES 1
#define CLK_PIN 11
#define CS_PIN 5
#define DATA_PIN 6

#define QUIT_BUTTON_PIN 2
#define ENTER_BUTTON_PIN 3
#define BUZZER_PIN 7
#define VIBRO_MOTOR_PIN 4
#define GYROSCOPE_ADDRESS 0x68

int rows = 8;
int cols = 8;

bool aPressed = false;
bool dPressed = false;
bool sPressed = false;
bool wPressed = false;

float deltaAngleX = 0;
float deltaAngleY = 0;

struct game* game;
Scheduler scheduler;
enum GAME_STATE gameState;
enum FEEDBACK_STATE feedbackState;

void setup() {
	randomSeed(analogRead(0));

	gameState = CHOOSE_GAME_MODE;
	feedbackState = OFF;
	game = (struct game*)malloc(sizeof(struct game));
	game->bestScore = 0;
	game->gameMode  = CLASSIC;
	game->world = (struct world*)malloc(sizeof(struct world));
	game->world->snake = (struct snake*)malloc(sizeof(struct snake));

	Gyroscope*  gyroscope   = new Gyroscope(GYROSCOPE_ADDRESS);
	VibroMotor* vibroMotor  = new VibroMotor(VIBRO_MOTOR_PIN); 
	Buzzer*     buzzer      = new Buzzer(BUZZER_PIN);
	Button*     quitButton  = new Button(QUIT_BUTTON_PIN);
	Button*     enterButton = new Button(ENTER_BUTTON_PIN);
	MD_MAX72XX* display     = new MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
	display->begin();

	calibrate(gyroscope, buzzer, display);

	GameControlsTask*    gameControlTask     = new GameControlsTask(gyroscope);
	GameTask*            gameTask		     		 = new GameTask();
	DisplayTask*         displayTask         = new DisplayTask(display);
	SensoryFeedbackTask* sensoryFeedbackTask = new SensoryFeedbackTask(buzzer, vibroMotor);
	sensoryFeedbackTask ->init(10);
	gameControlTask     ->init(10);
	gameTask            ->init(10);
	displayTask         ->init(5);

	scheduler.init(5);
	scheduler.addTask(gameControlTask);
	scheduler.addTask(gameTask);
	scheduler.addTask(displayTask);
	scheduler.addTask(sensoryFeedbackTask);

	enableInterrupt(quitButton->getPin(),  ManageInterrupt::QuitPressed,  RISING);
	enableInterrupt(enterButton->getPin(), ManageInterrupt::EnterPressed, RISING);
}

void loop() {
	scheduler.schedule();
}