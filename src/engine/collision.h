#ifndef COLLISION_H
#define COLLISION_H

typedef struct RECT {
    int x;
    int y;
    int width;
    int height;
} RECT;

int checkCollision(RECT* rec1, RECT* rec2);


int checkCollision(RECT* rec1, RECT* rec2) {
    // Right side rec1 < Left side rec2
    if (rec1->x + rec1->width < rec2->x) {
        return 0;
    }
    // Left side rec1 > Right side rec2
    if (rec1->x > rec2->x + rec2->width) {
        return 0;
    }

    // Top side rec1 > Bottom side rec2
    if (rec1->y > rec2->y + rec2->height) {
        return 0;
    }
    // Bottom side rec1 < Top side rec2
    if (rec1->y + rec1->height < rec2->y) {
        return 0;
    }
    
    return 1;
}

#endif