#ifndef SHOTLIST_H
#define SHOTLIST_H

#include "shot.h"
#include "enemy.h"
#include "player.h"

typedef struct shotList_t {
	shot* data;
	struct shotList_t* next;
} shotList_t;

shotList_t* createShotList() {
    shotList_t* result = (shotList_t*) malloc(1 * sizeof(shotList_t));
    result->data = 0;
    result->next = 0;

    return result;
}

void cleanUpShotList(shotList_t* current) {
    if (current->next != 0) {
        cleanUpShotList(current->next);
    }
    
    if (current->data != 0) {
        cleanUpShot(current->data);
    }
    free(current);
}


void pushShotlist(shotList_t* head, shot* nShot) {
	shotList_t* current = head;
	while(current->next != 0) {
		current = current->next;
	}

	current->next = (shotList_t*) malloc(1 * sizeof(shotList_t));
	current->next->data = nShot;
	current->next->next = 0;
}


void popShot(shotList_t** head) {
    shotList_t* next_node = 0;
    if (*head == 0) {
        return;
    }

    next_node = (*head)->next;
    free(*head);
    *head = next_node;
}
void removeShotList(shotList_t** head, shotList_t* elem) {
	shotList_t* current = *head;
    shotList_t* previous = *head;
	while(current != 0) {
		if (current == elem) {
			if (current == previous) {
                popShot(head);
                return;
            }

            previous->next = current->next;
            free(current);
		}

        previous = current;
		current = current->next;
	}
}


void invaderShoot(shotList_t** head, int x, int y) {
    shot* nShot = spawnShot(x, y, SHOT_SPEED, 1);
    if (nShot == 0) {
        return;
    }

    pushShotlist(*head, nShot);
}
void playerShoot(shotList_t** head, int x, int y) {
    shot* nShot = spawnShot(x, y, -SHOT_SPEED, 0);
    if (nShot == 0) {
        return;
    }

    pushShotlist(*head, nShot);
}

void moveShots(shotList_t** head) {
    shotList_t* current = *head;
    while(current != 0) {
        int worked = moveShot(current->data);
        if (worked == -1) {
            removeShotList(head, current);
        }

        current = current->next;
    }
}

void renderShots(shotList_t** head) {
    shotList_t* current = *head;
    while(current != 0) {
        renderShot(current->data);

        current = current->next;
    }
}


int checkEnemyHit(shotList_t** head, enemy* pEnemy) {
    shotList_t* current = *head;
    while(current != 0) {
        shot* data = current->data;
        if (data != 0) {
            if (data->fromPlayer) {
                int collided = enemyCheckShotCollision(pEnemy, data);
                if (collided) {
                    removeShotList(head, current);

                    return 1;
                }
            }
        }

        current = current->next;
    }

    return 0;
}

int checkPlayerHit(shotList_t** head, player* pPlayer) {
    shotList_t* current = *head;
    while(current != 0) {
        shot* data = current->data;
        if (data != 0) {
            if (!data->fromPlayer) {
                int collided = playerCheckShotCollision(pPlayer, data);
                if (collided) {
                    removeShotList(head, current);

                    return 1;
                }
            }
        }

        current = current->next;
    }

    return 0;
}

#endif