#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "shotList.h"
#include "enemyList.h"

typedef struct gameInfo {
    int lives;
    int score;
    int cyclesBeforeShot;
    player* user;
    shotList_t* shots;
    enemyList_t* enemys;
} gameInfo;

gameInfo* initGame(int minX, int maxX) {
    gameInfo* result = (gameInfo*) malloc(1 * sizeof(gameInfo));
    result->lives = 3;
    result->score = 0;
    result->cyclesBeforeShot = 0;

    // Spawn at bottom of Screen
	int center = ((maxX - minX) / 2) - (PLAYER_WIDTH / 2) - 1;
	result->user = spawnPlayer(center, 200);
	// Prepare the list of shots
	result->shots = createShotList();
	// Spawn the enemys
	result->enemys = createEnemylist();
	// First Line
	int first = 0;
	while (first < 11) {
		createEnemy(result->enemys, minX + first * 25, 25, ENEMY_SPEED, 1);
		first++;
	}
	// Second Line
	int second = 0;
	while (second < 11) {
		createEnemy(result->enemys, minX + second * 25, 50, ENEMY_SPEED, 2);
		second++;
	}
	// Third Line
	int third = 0;
	while (third < 11) {
		createEnemy(result->enemys, minX + third * 25, 75, ENEMY_SPEED, 3);
		third++;
	}

    return result;
}

void cleanUpGame(gameInfo* info) {
    cleanUpPlayer(info->user);
    cleanUpShotList(info->shots);
    cleanUpEnemyList(info->enemys);

    free(info);
}


void handlePlayerInput(int key, player* pPlayer, shotList_t** shotsHead, int* cycleBeforeNextShot, int min_X, int max_X) {
    if (key == 73 || key == 38) {
		pPlayer->x = move(pPlayer->x, -PLAYER_SPEED, max_X - PLAYER_WIDTH, min_X); // Move left
	} else if (key == 53 || key == 27) {
		pPlayer->x = move(pPlayer->x, PLAYER_SPEED, max_X - PLAYER_WIDTH, min_X);  // Move right
	} else if ((key == 63 || key == 28) && *cycleBeforeNextShot <= 0) {
		int center = pPlayer->x + (PLAYER_WIDTH / 2) - 1;
        playerShoot(shotsHead, center, pPlayer->y);  // Shoot up
		*cycleBeforeNextShot = 20;
	}
}

void sleepTicks(int ticks) {
	int RTC = RTC_GetTicks();
	int dRTC = 0;
	do {
		dRTC = RTC_GetTicks() - RTC;
	}while(dRTC < ticks);
}

int runGameCycle(gameInfo* info) {
    int key = getInput();

	if (key == KEY_PRGM_MENU) {
		while (1) {
			renderInGameUI();
			Bdisp_PutDisp_DD();
			

			int tmpKey = getInput();

			// The EXE key
			if (tmpKey == 31) {
				return -2;
			}
			// The EXIT key
			if (tmpKey == KEY_PRGM_EXIT) {
				break;
			}
		}
		return -1;
	}


	handlePlayerInput(key, info->user, &(info->shots), &(info->cyclesBeforeShot), MIN_X, MAX_X);

	// Updating Positions
	moveEnemys(&(info->enemys));
	moveShots(&(info->shots));

	// Selecting a random enemy and shooting
	enemy* tmpEnemy = getRandomEnemy(info->enemys);
	invaderShoot(&(info->shots), tmpEnemy->x, tmpEnemy->y);

	// Check for any collisions
	info->score += checkHits(&(info->enemys), &(info->shots));
	info->lives -= checkPlayerHit(&(info->shots), info->user);

	if (info->lives <= 0) {
		return 0;
	}
	int remaining = enemysRemaining(&(info->enemys));
	if (remaining <= 0) {
		return 1;
	}

	// Rendering Stuff
	renderEnemys(&(info->enemys));
	renderPlayer(info->user);
	renderShots(&(info->shots));

	drawRect(MIN_X, 0, 1, MAX_Y, 0);
	drawRect(MAX_X, 0, 1, MAX_Y, 0);
	renderGameUI(info->score, info->lives);

	Bdisp_PutDisp_DD();

	if (info->cyclesBeforeShot > 0) {
		info->cyclesBeforeShot--;
	}
	sleepTicks(10);

    return -1;
}


#endif