#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>

#include "movement.h"
#include "render.h"

#define ENEMY_SPEED 1
#define ENEMY_HEIGHT 16


typedef struct enemy {
    int x;
    int y;
    int deltaX;
    int type;
	int width;
} enemy;

enemy* spawnEnemy(int x, int y, int deltaX, int type) {
    enemy* tmp = (enemy*) malloc(1 * sizeof(enemy));
	tmp->x = x;
	tmp->y = y;
	tmp->deltaX = deltaX;
    tmp->type = type;

	if (type == 1) {
		tmp->width = 16;
	} else if (type == 2) {
		tmp->width = 22;
	} else if (type == 3) {
		tmp->width = 24;
	}

	return tmp;
}

void cleanUpEnemy(enemy* pEnemy) {
	free(pEnemy);
}

int moveEnemy(enemy* pEnemy) {
    if (pEnemy == 0) {
		return 0;
	}

    pEnemy->x = move(pEnemy->x, pEnemy->deltaX, MAX_X - pEnemy->width, MIN_X);
	if (pEnemy->x + pEnemy->width >= MAX_X || pEnemy->x == MIN_X) {
		return -1;
	}

	return 0;
}
void moveEnemyDown(enemy* pEnemy, int amount) {
    if (pEnemy == 0) {
		return;
	}

    pEnemy->y += amount;
}
void flipMovement(enemy* pEnemy) {
    pEnemy->deltaX *= -1;
}

void renderEnemy(enemy* pEnemy) {
	if (pEnemy == 0) {
		return;
	}

	int type = pEnemy->type;
	int x = pEnemy->x;
	int y = pEnemy->y;

	if (type == 1) {
		int sprite[8][8] = {
			{-1, -1, -1,  0,  0, -1, -1, -1},
			{-1, -1,  0,  0,  0,  0, -1, -1},
			{-1,  0,  0,  0,  0,  0,  0, -1},
			{ 0,  0, -1,  0,  0, -1,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0},
			{-1,  0, -1,  0,  0, -1,  0, -1},
			{ 0, -1, -1, -1, -1, -1, -1,  0},
			{-1,  0, -1, -1, -1, -1,  0, -1}
		};

		drawSprite(x, y, 8, 8, sprite, 2);
	} else if (type == 2) {
		int sprite[8][11] = {
			{-1, -1,  0, -1, -1, -1, -1, -1,  0, -1, -1},
			{-1, -1, -1,  0, -1, -1, -1,  0, -1, -1, -1},
			{-1, -1,  0,  0,  0,  0,  0,  0,  0, -1, -1},
			{-1,  0,  0, -1,  0,  0,  0, -1,  0,  0, -1},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{ 0, -1,  0, -1, -1, -1, -1, -1,  0, -1,  0},
			{-1, -1, -1,  0,  0, -1,  0,  0, -1, -1, -1}
		};

		drawSprite(x, y, 8, 11, sprite, 2);
	} else if (type == 3) {
		int sprite[8][12] = {
			{-1, -1, -1, -1,  0,  0,  0,  0, -1, -1, -1, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{ 0,  0,  0, -1, -1,  0,  0, -1, -1,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
			{-1, -1,  0,  0,  0, -1, -1,  0,  0,  0, -1, -1},
			{-1,  0,  0, -1, -1,  0,  0, -1, -1,  0,  0, -1},
			{-1, -1,  0,  0, -1, -1, -1, -1,  0,  0, -1, -1}
		};

		drawSprite(x, y, 8, 12, sprite, 2);
	}
}


int checkShotXCollision(enemy* pEnemy, shot* pShot) {
	if (pShot->x + SHOT_WIDTH < pEnemy->x) {
		return 0;
	}
	if (pShot->x > (pEnemy->x + pEnemy->width)) {
		return 0;
	}

	return 1;
}
int checkShotYCollision(enemy* pEnemy, shot* pShot) {
	if (pShot->y + SHOT_HEIGHT < pEnemy->y) {
		return 0;
	}
	if (pShot->y > pEnemy->y + ENEMY_HEIGHT) {
		return 0;
	}

	return 1;
}
int enemyCheckShotCollision(enemy* pEnemy, shot* pShot) {
	return (checkShotXCollision(pEnemy, pShot) && checkShotYCollision(pEnemy, pShot));
}

#endif