#ifndef UI_H
#define UI_H

#include "render.h"
#include "player.h"


void renderGameUI(int score, int lives) {
    unsigned char buffer[12];
	itoa(score, buffer);
	printMiniText(340, 10, buffer, COLOR_BLACK, COLOR_WHITE);

	int i = 0;
	while (i < lives - 1) {
	    drawPlayerModel(350, 60 + i * 20);
		i++;
	}
}

void renderInGameUI() {
	int x1 = 50;
	int x2 = LCD_WIDTH_PX - x1;
	int y1 = 30;
	int y2 = LCD_HEIGHT_PX - y1;


	TBdispFillArea areaToFill;
	areaToFill.x1 = x1;
	areaToFill.y1 = y1;
	areaToFill.x2 = x2;
	areaToFill.y2 = y2;
	areaToFill.mode = (unsigned char) 0;
	Bdisp_AreaClr(&areaToFill, 0, 0);

	unsigned char* pauseMessage = (unsigned char*) "PAUSED";
	printCenteredMiniText(x1, x2, y1 + 10, pauseMessage, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continuePart = (unsigned char*) "Press EXIT to continue...";
	printCenteredMiniText(x1, x2, y2 - 50, continuePart, COLOR_BLACK, COLOR_WHITE);

	unsigned char* exitPart = (unsigned char*) "Press EXE to exit to the Main Menu";
	printCenteredMiniText(x1, x2, y2 - 25, exitPart, COLOR_BLACK, COLOR_WHITE);
}

void renderEndScreen(int won, int score) {
    if (won) {
	    unsigned char* endMessage = (unsigned char*) "YOU WON!";
		printCenterMiniText(0, endMessage, COLOR_BLACK, COLOR_WHITE);
	}else {
		unsigned char* endMessage = (unsigned char*) "YOU LOST!";
		printCenterMiniText(0, endMessage, COLOR_BLACK, COLOR_WHITE);
	}

    unsigned char* scoreMessage = (unsigned char*) "Score:";
    printCenterMiniText(50, scoreMessage, COLOR_BLACK, COLOR_WHITE);

    unsigned char buffer[12];
	itoa(score, buffer);
	printCenterMiniText(70, buffer, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continueMessage = (unsigned char*) "Press any button to continue...";
	printCenterMiniText(150, continueMessage, COLOR_BLACK, COLOR_WHITE);
}

void renderMainMenu() {
    unsigned char* mainMenuScreen = (unsigned char*) "Space Invaders";
	printCenterMiniText(0, mainMenuScreen, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continueMessage = (unsigned char*) "Press any button to start...";
	printCenterMiniText(75, continueMessage, COLOR_BLACK, COLOR_WHITE);
}


#endif