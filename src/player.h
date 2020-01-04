#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>

#include "engine/collision.h"
#include "engine/render.h"
#include "movement.h"

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

	renderSprite(x, y, 6, 11, sprite, 2);
}

void renderPlayer(player* pPlayer) {
	if (pPlayer == 0) {
		return;
	}

	drawPlayerModel(pPlayer->x, pPlayer->y);
}


int playerCheckShotCollision(player* pPlayer, shot* pShot) {
  RECT playerRect = {
    .x = pPlayer->x,
    .y = pPlayer->y,
    .width = PLAYER_WIDTH,
    .height = PLAYER_HEIGHT,
  };
  RECT shotRect = {
    .x = pShot->x,
    .y = pShot->y,
    .width = SHOT_WIDTH,
    .height = SHOT_HEIGHT,
  };

	return checkCollision(&playerRect, &shotRect);
}

#endif
