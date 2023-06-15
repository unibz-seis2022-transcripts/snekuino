#include "Calibration.h"
#include "snake.h"
#include "Notes.h"

#define CALIBRATION_TIME 200

extern float deltaAngleX;
extern float deltaAngleY;

enum HOURGLASS_STATE {
    TOP,
    HALF,
    BOTTOM
};

struct position hourGlassPixels[] = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0},
    {6, 0},
    {7, 0},
    {0, 1},
    {7, 1},
    {1, 2},
    {6, 2},
    {2, 3},
    {5, 3},
    {3, 4},
    {4, 4},
    {2, 5},
    {5, 5},
    {1, 6},
    {6, 6},
    {0, 7},
    {1, 7},
    {2, 7},
    {3, 7},
    {4, 7},
    {5, 7},
    {6, 7},
    {7, 7},
};

int hourGlassPixelLength = 28;

struct position sandTop[] = {
    {4, 1},
    {3, 2},
    {4, 3},

    {3, 5},
    {4, 5},
    {2, 6},
    {3, 6},
    {4, 6},
    {5, 6},
};

struct position sandHalf[] = {
    {1, 1},
    {2, 1},
    {3, 1},
    {4, 1},
    {5, 1},
    {6, 1},
    {4, 2},
    {3, 3},
    {3, 5},
    {4, 5},
};

struct position sandBottom[] = {
    {1, 1},
    {2, 1},
    {3, 1},
    {4, 1},
    {5, 1},
    {6, 1},
    {2, 2},
    {3, 2},
    {4, 2},
    {5, 2},
    {4, 3},
};

int sandLengths[] = { 9, 10, 11 };

void displayHourGlass(enum HOURGLASS_STATE state, MD_MAX72XX* display) {
    display->clear();
    display->control(display->INTENSITY, MAX_INTENSITY);

    for (int i = 0; i < hourGlassPixelLength; i++) {
        display->setPoint(hourGlassPixels[i].y, hourGlassPixels[i].x, true);
    }

    display->clear();
    display->control(display->INTENSITY, MAX_INTENSITY/4);
    switch (state)
    {
    case TOP:
        for (int i = 0; i < sandLengths[0]; i++) {
            display->setPoint(sandTop[i].y, sandTop[i].x, true);
        }
        break;
    case HALF:
        for (int i = 0; i < sandLengths[1]; i++) {
            display->setPoint(sandHalf[i].y, sandHalf[i].x, true);
        }
        break;
    case BOTTOM:
        for (int i = 0; i < sandLengths[2]; i++) {
            display->setPoint(sandBottom[i].y, sandBottom[i].x, true);
        }
        break;
    }
}

void calibrationCompleteTune (Buzzer* buzzer) {
    float multiplier = .6;
    buzzer->playSound(NOTE_A * multiplier, 100);
    delay(100);
    buzzer->playSound(NOTE_C_SHARP * multiplier, 150);
    delay(150);
    buzzer->playSound(NOTE_A * 2 * multiplier, 300);
    delay(1000);
}

void calibrate(Gyroscope* gyroscope, Buzzer* buzzer, MD_MAX72XX* display) {
    enum HOURGLASS_STATE hourglassState = TOP;
    int calibrationTime = 0;
    while (calibrationTime < CALIBRATION_TIME) {
        displayHourGlass(hourglassState, display);
        if (calibrationTime % 10 == 0) {
            deltaAngleX = gyroscope->getAngleX();
            deltaAngleY = gyroscope->getAngleY();
        }
        if (calibrationTime % 30 == 0) {
            hourglassState = (HOURGLASS_STATE)((hourglassState+1)%3);
        }
        calibrationTime += 1;
    }
    display->clear();
    calibrationCompleteTune(buzzer);
}