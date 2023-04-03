#include "canvas.h"
#include "snake.h"

extern int rows;
extern int cols;

void clearPixels() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			canvasSetPixel(i, j, 0);
		}
	}
}

void drawPixels(position* pixels, int length) {
	for (int i = 0; i < length; i++) {
		position pixel = pixels[i];
		canvasSetPixel(pixel.x, pixel.y, 0.8);
	}
}