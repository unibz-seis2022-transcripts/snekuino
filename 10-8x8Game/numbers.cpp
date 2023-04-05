#include "numbers.h"
#include <stdlib.h>
#include "pixelhelper.h"

position numberOnePixels[] = {
	{ 2, 4 },
	{ 1, 3 },
	{ 2, 3 },
	{ 2, 2 },
	{ 2, 1 },
	{ 2, 0 },
};

position numberTwoPixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 0, 1 },
	{ 0, 0 },
	{ 0, 1 },
	{ 0, 2 },
};

position numberThreePixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 2, 1 },
	{ 1, 0 },
	{ 0, 0 },
};

position numberFourPixels[] = {
	{ 2, 4 },
	{ 1, 3 },
	{ 0, 2 },
	{ 0, 1 },
	{ 1, 1 },
	{ 2, 1 },
	{ 2, 0 },
};

position numberFivePixels[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 1 },
	{ 1, 2 },
	{ 0, 3 },
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
};

position numberSixPixels[] = {
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

position numberSevenPixels[] = {
	{ 0, 4 },
	{ 1, 4 },
	{ 2, 4 },
	{ 2, 3 },
	{ 1, 2 },
	{ 1, 1 },
	{ 1, 0 },
};

position numberEightPixels[] = {
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

position numberNinePixels[] = {
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

position numberZeroPixels[] = {
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

struct pixelAndLength {
	position* pixels;
	int length;
};



struct pixelAndLength* digitPixelArrays[] = {
	{numberZeroPixels[0], 1}
	/*numberOnePixels,
	numberTwoPixels,
	numberThreePixels,
	numberFourPixels,
	numberFivePixels,
	numberSixPixels,
	numberSevenPixels,
	numberEightPixels,
	numberNinePixels,*/
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
	struct position pixels[] = digitPixelArrays[digit];
	int lengthPixels = sizeof(pixels) / sizeof(pixels[0]);

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
