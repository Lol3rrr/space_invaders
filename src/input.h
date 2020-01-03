#ifndef INPUT_H
#define INPUT_H

#include <keyboard.h>

int getInput(void) {
	unsigned char buffer[12];
	PRGM_GetKey_OS(buffer);
	
	return (buffer[1] & 0x0F) * 10 + ((buffer[2] & 0xF0) >> 4);
}

#endif