#ifndef RENDER_H
#define RENDER_H

#include <display_syscalls.h>
#include <display.h>
#include <color.h>

#define DISPLAY_WIDTH 384
#define DISPLAY_HEIGHT 216
#define vram 0xAC000000

#define EMPTY_PIXEL -1

// Create Colors using this Pattern
// 0b 00000 000000 00000
//      R     G      B
#define C_BLACK 0b0000000000000000
#define C_WHITE 0b1111111111111111
#define C_RED   0b1111100000000000
#define C_GREEN 0b0000011111100000
#define C_BLUE  0b0000000000011111

void renderPixel(int x, int y, int color);
void renderRect(int x, int y, int width, int height, int color);
void renderSprite(int x, int y, int height, int width, int data[height][width], int scaleFactor);
void renderCenteredMiniText(int x1, int x2, int pY, unsigned char* text, color_t fore, color_t back);
void renderCenterMiniText(int y, unsigned char* text, color_t fore, color_t back);
void renderMiniText(int x, int y, unsigned char* text, color_t fore, color_t back);


void renderPixel(int x, int y, int color) {
	if (x > DISPLAY_WIDTH || x < 0) {
		return;
	}
	if (y > DISPLAY_HEIGHT || y < 0) {
		return;
	}

	unsigned short* p = (unsigned short*) vram;
	p += (DISPLAY_WIDTH * y) + x;
	*p = color;
}

void renderRect(int pX, int pY, int width, int height, int color) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			renderPixel(pX + x, pY + y, color);
		}
	}
}

void renderSprite(int pX, int pY, int height, int width, int data[height][width], int scaleFactor) {
  int tmpY = pY;
  for (int y = 0; y < height; y++) {
    for (int yS = 0; yS < scaleFactor; yS++) {
      int tmpX = pX;
      for (int x = 0; x < width; x++) {
        int color = data[y][x];

        for (int xS = 0; xS < scaleFactor; xS++) {
          if (color != EMPTY_PIXEL) {
            renderPixel(tmpX, tmpY, color);
          }

          tmpX++;
        }
      }

      tmpY++;
    }
  }
}

void renderCenteredMiniText(int x1, int x2, int pY, unsigned char* text, color_t fore, color_t back) {
    int rawCenter = (x2 - x1) / 2 - 1;

	int x = 0;
	int y = 0;
	PrintMini(&x, &y, text, 0, 0xFFFFFFFF, 0, 0, fore, back, 0, 0);

	int center = rawCenter - (x / 2 - 1) + x1;
	y = pY;
	PrintMini(&center, &y, text, 0, 0xFFFFFFFF, 0, 0, fore, back, 1, 0);
}

void renderCenterMiniText(int y, unsigned char* text, color_t fore, color_t back) {
	renderCenteredMiniText(0, DISPLAY_WIDTH, y, text, fore, back);
}

void renderMiniText(int x, int y, unsigned char* text, color_t fore, color_t back) {
    PrintMini(&x, &y, text, 0, 0xFFFFFFFF, 0, 0, fore, back, 1, 0);
}


#endif
