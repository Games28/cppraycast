#ifndef FORCE_POWERS_H
#define FORCE_POWERS_H
#include "textures.h"
#include "player.h"
#include "sprite.h"
#include "Vec2.h"
#include "graphics.h"

class force_powers
{
public:
	void update(graphics& gfx, Player& player, Sprites& sprite, Texture& texture);
	bool isinsight(Sprite& sprite, Player& player, float fov, float& angle2player);
	void TKmove(Sprite& sprite, Player& player);
	void TKstrafe(Sprite& sprite, Player& player);
	void TKrotation(Sprite& sprite, Player& player);
	void Draw(graphics& gfx, Texture& texture, int textureid);

public:
	Sprite* spr = nullptr;

};


#endif // !FORCE_POWERS_H



