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
	int texture;
	int lift;
	float scale;
	int downscale;
	float spritescale;
	float distance;
	float angle;
	bool visible;
	
	
	
}sprite_t;



void spriteinput();
void initsprite();
void renderSpriteProjection();
void renderMapSprites();


#endif // !SPRITE_H