#include "score.h"
#include "canvas.h"
#include "numbers.h"
#include "pixelhelper.h"

void updateScorePixels(int score) {
	clearPixels();
	drawNumber(score);
}

void promptScore(int score) {
	while (canvasUpdate() == 0)
	{
		if (qPressed) {
			canvasClose();
			break;
		}
		updateScorePixels(score);
		repaint();
	}
}
