#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include "enemy.h"
#include "shotList.h"

typedef struct enemyList_t {
	enemy* data;
	struct enemyList_t* next;
} enemyList_t;

enemyList_t* createEnemylist() {
    enemyList_t* result = (enemyList_t*) malloc(1 * sizeof(enemyList_t));
    result->data = 0;
    result->next = 0;

    return result;
}

void cleanUpEnemyList(enemyList_t* current) {
    if (current->next != 0) {
        cleanUpEnemyList(current->next);
    }
    
    if (current->data != 0) {
        cleanUpEnemy(current->data);
    }
    free(current);
}

enemy* getRandomEnemy(enemyList_t* head) {
    enemyList_t* current = head;
    while(current->next != 0) {
        if (current->data != 0) {
            if ((rand() % 3) == 0) {
                return current->data;
            }
        }

		current = current->next;
	}

    return current->data;
}


void pushEnemylist(enemyList_t* head, enemy* nEnemy) {
	enemyList_t* current = head;
	while(current->next != 0) {
		current = current->next;
	}

	current->next = (enemyList_t*) malloc(1 * sizeof(enemyList_t));
	current->next->data = nEnemy;
	current->next->next = 0;
}
void createEnemy(enemyList_t* head, int x, int y, int deltaX, int type) {
    enemy* tmp = spawnEnemy(x, y, deltaX, type);
    pushEnemylist(head, tmp);
}


void popEnemy(enemyList_t** head) {
    enemyList_t* next_node = 0;
    if (*head == 0) {
        return;
    }

    next_node = (*head)->next;
    free(*head);
    *head = next_node;
}
void removeEnemyList(enemyList_t** head, enemyList_t* elem) {
	enemyList_t* current = *head;
    enemyList_t* previous = *head;
	while(current != 0) {
		if (current == elem) {
			if (current == previous) {
                popEnemy(head);
                return;
            }

            previous->next = current->next;
            free(current);
		}

        previous = current;
		current = current->next;
	}
}


void moveEnemysDownNFlip(enemyList_t** head) {
    enemyList_t* current = *head;
    while(current != 0) {
        moveEnemyDown(current->data, 5);
        flipMovement(current->data);

        current = current->next;
    }
}
void moveEnemys(enemyList_t** head) {
    int reachedEnd = 0;

    enemyList_t* current = *head;
    while(current != 0) {
        int worked = moveEnemy(current->data);
        if (worked == -1) {
            reachedEnd = 1;
        }

        current = current->next;
    }

    if (reachedEnd) {
        moveEnemysDownNFlip(head);
    }
}

void renderEnemys(enemyList_t** head) {
    enemyList_t* current = *head;
    while(current != 0) {
        renderEnemy(current->data);

        current = current->next;
    }
}


int getPoints(enemy* pEnemy) {
    if (pEnemy->type == 1) {
        return 50;
    }
    if (pEnemy->type == 2) {
        return 25;
    }
    if (pEnemy->type == 3) {
        return 10;
    }

    return 0;
}
int checkHits(enemyList_t** head, shotList_t** shots) {
    int total = 0;

    enemyList_t* current = *head;
    while (current != 0) {
        enemy* data = current->data;
        if (data != 0) {
            int hit = checkEnemyHit(shots, data);

            if (hit) {
                total += getPoints(data);

                enemyList_t* old = current;
                current = current->next;
                removeEnemyList(head, old);
                
                continue;
            }
        }

        current = current->next;
    }

    return total;
}

int enemysRemaining(enemyList_t** head) {
    int total = 0;

    enemyList_t* current = *head;
    while (current != 0) {
        enemy* data = current->data;
        if (data != 0) {
            total++;
        }

        current = current->next;
    }

    return total;
}


#endif