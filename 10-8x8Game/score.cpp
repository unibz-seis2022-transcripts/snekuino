#include "score.h"
#include "canvas.h"
#include "numbers.h"
#include "pixelhelper.h"

void updateScorePixels(int score) {
	clearPixels();
	drawNumber(score, 1);
}

void promptScore(int score) {
	int delay = 1000;
	while (canvasUpdate() == 0) {
		if (qPressed || delay <= 0) {
			canvasClose();
			break;
		}
		updateScorePixels(score);
		repaint();
		delay--;
	}
}
