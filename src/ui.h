#ifndef UI_H
#define UI_H

#include "engine/render.h"
#include "player.h"


void renderGameUI(int score, int lives) {
  unsigned char buffer[12];
	itoa(score, buffer);
	renderMiniText(340, 10, buffer, COLOR_BLACK, COLOR_WHITE);

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

  int spriteData[1][1] = {
    {C_WHITE}
  };
  renderSprite(x1, y1, 1, 1, spriteData, (x2 - x1));

	unsigned char* pauseMessage = (unsigned char*) "PAUSED";
	renderCenteredMiniText(x1, x2, y1 + 10, pauseMessage, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continuePart = (unsigned char*) "Press EXIT to continue...";
	renderCenteredMiniText(x1, x2, y2 - 50, continuePart, COLOR_BLACK, COLOR_WHITE);

	unsigned char* exitPart = (unsigned char*) "Press EXE to exit to the Main Menu";
	renderCenteredMiniText(x1, x2, y2 - 25, exitPart, COLOR_BLACK, COLOR_WHITE);
}

void renderEndScreen(int won, int score) {
  if (won) {
	   unsigned char* endMessage = (unsigned char*) "YOU WON!";
		renderCenterMiniText(0, endMessage, COLOR_BLACK, COLOR_WHITE);
	}else {
		unsigned char* endMessage = (unsigned char*) "YOU LOST!";
		renderCenterMiniText(0, endMessage, COLOR_BLACK, COLOR_WHITE);
	}

  unsigned char* scoreMessage = (unsigned char*) "Score:";
  renderCenterMiniText(50, scoreMessage, COLOR_BLACK, COLOR_WHITE);

  unsigned char buffer[12];
	itoa(score, buffer);
	renderCenterMiniText(70, buffer, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continueMessage = (unsigned char*) "Press any button to continue...";
	renderCenterMiniText(150, continueMessage, COLOR_BLACK, COLOR_WHITE);
}

void renderMainMenu() {
  unsigned char* mainMenuScreen = (unsigned char*) "Space Invaders";
	renderCenterMiniText(0, mainMenuScreen, COLOR_BLACK, COLOR_WHITE);

	unsigned char* continueMessage = (unsigned char*) "Press any button to start...";
	renderCenterMiniText(75, continueMessage, COLOR_BLACK, COLOR_WHITE);
}


#endif
