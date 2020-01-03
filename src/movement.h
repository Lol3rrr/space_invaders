#ifndef MOVEMENT_H
#define MOVEMENT_H

int move(int cord, int delta, int max, int min) {
	if (cord + delta < min) {
		return min;
	}
	if (cord + delta > max) {
		return max;
	}
	return cord + delta;
}

#endif