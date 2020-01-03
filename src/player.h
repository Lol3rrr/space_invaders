#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>

#include "movement.h"
#include "render.h"

#include "shot.h"

#define PLAYER_SPEED 3
#define PLAYER_WIDTH 22
#define PLAYER_HEIGHT 12

typedef struct player {
    int x;
    int y;
} player;

player* spawnPlayer(int x, int y) {
    player* tmp = (player*) malloc(1 * sizeof(player));
	tmp->x = x;
	tmp->y = y;

	return tmp;
}

void cleanUpPlayer(player* pPlayer) {
	free(pPlayer);
}

void drawPlayerModel(int x, int y) {
	int sprite[6][11] = {
		{-1, -1, -1, -1, -1,  0, -1, -1, -1, -1, -1},
		{-1, -1, -1, -1,  0,  0,  0, -1, -1, -1, -1},
		{-1, -1, -1, -1,  0,  0,  0, -1, -1, -1, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};

	drawSprite(x, y, 6, 11, sprite, 2);
}

void renderPlayer(player* pPlayer) {
	if (pPlayer == 0) {
		return;
	}

	drawPlayerModel(pPlayer->x, pPlayer->y);
}


int playerCheckShotXCollision(player* pPlayer, shot* pShot) {
	if (pShot->x + SHOT_WIDTH < pPlayer->x) {
		return 0;
	}
	if (pShot->x > (pPlayer->x + PLAYER_WIDTH)) {
		return 0;
	}

	return 1;
}
int playerCheckShotYCollision(player* pPlayer, shot* pShot) {
	if (pShot->y + SHOT_HEIGHT < pPlayer->y) {
		return 0;
	}
	if (pShot->y > pPlayer->y + PLAYER_HEIGHT) {
		return 0;
	}

	return 1;
}
int playerCheckShotCollision(player* pPlayer, shot* pShot) {
	return (playerCheckShotXCollision(pPlayer, pShot) && playerCheckShotYCollision(pPlayer, pShot));
}

#endif