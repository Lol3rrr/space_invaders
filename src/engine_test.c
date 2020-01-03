#include <display_syscalls.h>
#include <disp_tools.hpp>
#include <color.h>
#include <keyboard_syscalls.h>
#include <keyboard.h>
#include <keyboard.hpp>
#include <CONVERT_syscalls.h> 
#include <SYSTEM_syscalls.h>
#include <STD_syscalls.h> 
#include <rtc.h> 

#include "movement.h"
#include "render.h"

#include "player.h"
#include "shot.h"
#include "shotList.h"
#include "enemy.h"
#include "enemyList.h"
#include "input.h"
#include "ui.h"

#include "game.h"

#define RUNNING 1
#define END_SCREEN 0
#define MAIN_MENU -1


int main(void) {
	Bdisp_AllClr_VRAM();

	gameInfo* info = initGame(MIN_X, MAX_X);

	int status = MAIN_MENU;
	int won = 0;

	while (1) {
		Bdisp_AllClr_VRAM();

		if (status == RUNNING) {
			int result = runGameCycle(info);
			if (result == -2) {
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