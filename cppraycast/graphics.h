#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>

#include <SDL.h>

#include "defs.h"


class graphics
{
public:
	bool initializeWindow(void);
	void destroyWindow(void);
	void clearColorBuffer(color_t color);
	void renderColorBuffer(void);
	void drawPixel(int x, int y, color_t color);
	void drawRect(int x, int y, int width, int height, color_t color);
	void drawLine(int x0, int y0, int x1, int y1, color_t color);

public:
	SDL_Window   *window             = NULL;
    SDL_Renderer *renderer           = NULL;
	color_t      *colorBuffer        = NULL;
	SDL_Texture  *colorBufferTexture = NULL;
};

#endif  // ifndef GRAPHICS_H
