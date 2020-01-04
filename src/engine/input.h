#ifndef INPUT_H
#define INPUT_H

#include <keyboard.h>

#define KEY_LEFT  38
#define KEY_DOWN  37
#define KEY_UP    28
#define KEY_RIGHT 27

#define KEY_MENU 48
#define KEY_EXIT 47
#define KEY_EXE  31

#define KEY_0 71
#define KEY_1 72
#define KEY_2 62
#define KEY_3 52
#define KEY_4 73
#define KEY_5 63
#define KEY_6 53
#define KEY_7 74
#define KEY_8 64
#define KEY_9 54

int getInput_NonBlocking();


int getInput_NonBlocking() {
	unsigned char buffer[12];
	PRGM_GetKey_OS(buffer);

	return (buffer[1] & 0x0F) * 10 + ((buffer[2] & 0xF0) >> 4);
}

#endif
