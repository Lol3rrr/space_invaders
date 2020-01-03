#ifndef SHOT_H
#define SHOT_H

#include <stdlib.h>

#include "movement.h"
#include "render.h"

#define SHOT_SPEED 2
#define SHOT_WIDTH 2
#define SHOT_HEIGHT 6

typedef struct shot {
	int x;
	int y;
	int deltaY;
	int fromPlayer;
} shot;


shot* spawnShot(int x, int y, int delta, int byEnemy) {
	if (byEnemy) {
		if ((rand() % 25) != 0) {
			return 0;
		}
	}

	shot* tmp = (shot*) malloc(1 * sizeof(shot));
	tmp->x = x;
	tmp->y = y + delta;
	tmp->deltaY = delta;
	tmp->fromPlayer = !byEnemy;

	return tmp;
}

void cleanUpShot(shot* pShot) {
	free(pShot);
}

int moveShot(shot* pShot) {
	if (pShot == 0) {
		return 0;
	}

	pShot->y = move(pShot->y, pShot->deltaY, MAX_Y, MIN_Y);
	if (pShot->y == MAX_Y || pShot->y == MIN_Y) {
		return -1;
	}

	return 0;
}
void renderShot(shot* pShot) {
	if (pShot == 0) {
		return;
	}
	
	drawRect(pShot->x, pShot->y, SHOT_WIDTH, SHOT_HEIGHT, 0);
}

#endif