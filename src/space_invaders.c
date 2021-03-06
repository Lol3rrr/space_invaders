#include <display_syscalls.h>
#include <keyboard.h>
#include <keyboard.hpp>
#include <CONVERT_syscalls.h>

#include "ui.h"
#include "game.h"

#define RUNNING 1
#define END_SCREEN 0
#define MAIN_MENU -1


int main() {
	Bdisp_AllClr_VRAM();

	gameInfo* info = initGame(MIN_X, MAX_X);

	int status = MAIN_MENU;
	int won = 0;

	while (1) {
		Bdisp_AllClr_VRAM();

		if (status == RUNNING) {
			int result = runGameCycle(info);
			if (result == -2) {
				status = MAIN_MENU;
				return 0;
			}
			if (result == -1) {
				continue;
			}

			won = result;
			status = END_SCREEN;
		} else if (status == END_SCREEN) {
			renderEndScreen(won, info->score);
			Bdisp_PutDisp_DD();

			int key;
			GetKey(&key);

			status = MAIN_MENU;
		} else if (status == MAIN_MENU) {
			renderMainMenu();
			Bdisp_PutDisp_DD();

			int key;
			GetKey(&key);

			cleanUpGame(info);
			info = initGame(MIN_X, MAX_X);

			status = RUNNING;
		}
	}

	return 0;
}
