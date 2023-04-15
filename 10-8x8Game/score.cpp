#include "score.h"
#include "canvas.h"
#include "numbers.h"
#include "pixelhelper.h"

void updateSnekPixels(int score) {
	clearPixels();
	drawNumber(score, 1);
}

void promptScore(int score) {
	int delay = 800;
	while (canvasUpdate() == 0) {
		if (enterPressed || delay <= 0) {
			return;
		}
		updateSnekPixels(score);
		repaint();
		delay-=10;
	}
}
