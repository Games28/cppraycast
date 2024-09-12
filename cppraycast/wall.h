#ifndef WALL_H
#define WALL_H

#include "textures.h"
#include "defs.h"
#include "player.h"
#include "ray.h"
#include "graphics.h"

struct sDelayedPixel {
    int x;
    int y;
    uint32_t p;
};
typedef struct sDelayedPixel DelayedPixel;

class Wall
{
public:
	void changeColorIntensity(color_t* color, float factor);
	void renderWallProjection(graphics& gfx, Rays& ray, Player& player, Texture& texture);
	void calculateBottomAndTop(int sliceheight, int halfheight, float wallheight,
		int& wallceil, int& wallfloor, Player& player);
};

#endif // !WALL_H


