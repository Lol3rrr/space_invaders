#ifndef RENDER_H
#define RENDER_H

#include <fxCG_Display.h>
#include <display.h>
#include <color.h>

#define MIN_X 5
#define MAX_X 330
#define MIN_Y 0
#define MAX_Y 215

unsigned short* vram = (unsigned short*) 0xAC000000;

void draw_pixel(int pX, int pY, int white) {
	if (pX > LCD_WIDTH_PX || pX < 0) {
		return;
	}
	if (pY > LCD_HEIGHT_PX || pY < 0) {
		return;
	}

	unsigned short* p = vram;
	p += LCD_WIDTH_PX * (pY) + pX;
	*p = white;
}

void drawRect(int x, int y, int width, int height, int white) {
	int tmpX = 0;
	while (tmpX < width) {
		int tmpY = 0;
		while (tmpY <= height) {
			draw_pixel(x + tmpX, y + tmpY, white);
			
			tmpY++;
		}

		tmpX++;
	}
}

void drawLine(int x, int y, int line[], int lineLength, int scaleFactor) {
	int i = 0;
	int tmpX = x;
	while (i < lineLength) {
		int color = line[i];

		int s = 0;
		while (s < scaleFactor) {
			if (color != -1) {
				draw_pixel(tmpX, y, color);
			}
			
			tmpX++;
			s++;
		}
		
		i++;
	}
}

void drawSprite(int x, int y, int spriteHeight, int spriteWidth, int sprite[spriteHeight][spriteWidth], int scaleFactor) {
	int i = 0;
	int tmpY = y;
	while (i < spriteHeight) {
		int s = 0;
		while (s < scaleFactor) {
			drawLine(x, tmpY, sprite[i], spriteWidth, scaleFactor);

			tmpY++;
			s++;
		}

		i++;
	}
}

void printCenteredMiniText(int x1, int x2, int pY, unsigned char* text, color_t foreColor, color_t backColor) {
	int rawCenter = (x2 - x1) / 2 - 1;

	int x = 0;
	int y = 0;
	PrintMini(&x, &y, text, 0, 0xFFFFFFFF, 0, 0, foreColor, backColor, 0, 0);

	int center = rawCenter - (x / 2 - 1) + x1;
	y = pY;
	PrintMini(&center, &y, text, 0, 0xFFFFFFFF, 0, 0, foreColor, backColor, 1, 0);
}

void printCenterMiniText(int pY, unsigned char* text, color_t foreColor, color_t backColor) {
	printCenteredMiniText(0, LCD_WIDTH_PX, pY, text, foreColor, backColor);
}

void printMiniText(int x, int y, unsigned char* text, color_t foreColor, color_t backColor) {
	PrintMini(&x, &y, text, 0, 0xFFFFFFFF, 0, 0, foreColor, backColor, 1, 0);
}

#endif