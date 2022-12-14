#ifndef SPRITE_H
#define SPRITE_H
#include "textures.h"
#include "graphics.h"
#include "player.h"

#include "defs.h"
#include "utils.h"
#include "ray.h"


typedef struct
{
	float x;
	float y;
	float distance;
	float angle;
	bool visible;
	int texture;
}sprite_t;


void renderSpriteProjection();
void renderMapSprites();


#endif // !SPRITE_H