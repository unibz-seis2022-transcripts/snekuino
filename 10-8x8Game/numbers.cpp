#include "numbers.h"
#include <stdlib.h>
#include "pixelhelper.h"

struct position numberOnePixels[] = {
	{ 2, 4 },
	{ 1, 3 },
	{ 2, 3 },
	{ 2, 2 },
	{ 2, 1 },
	{ 2, 0 },
};

struct position numberTwoPixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 0, 1 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
};

struct position numberThreePixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 2, 1 },
	{ 1, 0 },
	{ 0, 0 },
};

struct position numberFourPixels[] = {
	{ 2, 4 },
	{ 1, 3 },
	{ 0, 2 },
	{ 0, 1 },
	{ 1, 1 },
	{ 2, 1 },
	{ 2, 0 },
};

struct position numberFivePixels[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 1 },
	{ 1, 2 },
	{ 0, 3 },
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
};

struct position numberSixPixels[] = {
	{ 2, 4 },
	{ 1, 4 },
	{ 0, 4 },
	{ 0, 3 },
	{ 0, 2 },
	{ 0, 1 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 2, 1 },
	{ 2, 2 },
	{ 1, 2 },
};

struct position numberSevenPixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 1, 1 },
	{ 1, 0 },
};

struct position numberEightPixels[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 0, 1 },
	{ 2, 1 },
	{ 0, 2 },
	{ 1, 2 },
	{ 2, 2 },
	{ 0, 3 },
	{ 2, 3 },
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
};

struct position numberNinePixels[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 1 },
	{ 0, 2 },
	{ 1, 2 },
	{ 2, 2 },
	{ 0, 3 },
	{ 2, 3 },
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
};

struct position numberZeroPixels[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 0, 1 },
	{ 2, 1 },
	{ 0, 2 },
	{ 2, 2 },
	{ 0, 3 },
	{ 2, 3 },
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
};

struct position* digitPixelArrays[] = {
	numberZeroPixels,	
	numberOnePixels,  
	numberTwoPixels,	
	numberThreePixels,
	numberFourPixels,	
	numberFivePixels,	
	numberSixPixels,	
	numberSevenPixels,
	numberEightPixels,
	numberNinePixels,	
};

int lengths[] = {
	12,
	6,
	8,
	8,
	7,
	8,
	12,
	7,
	13,
	12,
};

struct position* translatePixels(struct position* pixels, int lengthPixels, int translateX, int translateY) {
	struct position* translatedPositions = (struct position*) malloc(lengthPixels * sizeof(struct position));
	for (int i = 0; i < lengthPixels; i++) {
		translatedPositions[i] = { pixels[i].x + translateX,  pixels[i].y + translateY };
	}
	return translatedPositions;
};

void drawDigit(int value, int translateX, int translateY) {
	int digit = value % 10;
	struct position* pixels = digitPixelArrays[digit];
	int lengthPixels = lengths[digit];

	struct position* translatedPixels = translatePixels(pixels, lengthPixels, translateX, translateY);
	drawPixels(translatedPixels, lengthPixels);
}

void drawNumber(int value, int translateY) {
	// Make sure to only print values < 100
	int twoDigitValue = value % 100;
	int leftDigit = value / 10;
	int rightDigit = value % 10;
	
	int translateXLeft = 0;
	int translateXRight = 4;
	drawDigit(leftDigit, translateXLeft, translateY);
	drawDigit(rightDigit, translateXRight, translateY);
}
