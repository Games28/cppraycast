#include "force_powers.h"

void force_powers::update(graphics& gfx, Player& player, Sprites& sprite, Texture& texture)
{
	float fobjplyA;
	Draw(gfx, texture, 0);

	if (!sprite.istargeted)
	{
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			spr = &sprite.sprites[i];
			spr->insight = isinsight(*spr, player, 10.0f * (3.14159f / 180.0f), fobjplyA);
			if (spr->insight)
			{
				spr->islifting = true;

				Draw(gfx, texture, 1);
			}
			spr->isfalling = true;
		}
	}
	else
	{
		if (spr->islifting)
		{
			Draw(gfx, texture, 1);
			TKmove(*spr, player);
			TKstrafe(*spr, player);
			TKrotation(*spr, player);
		}
		else
		{
			spr = nullptr;


		}
	}
}

bool force_powers::isinsight(Sprite& sprite, Player& player, float fov, float& angle2player)
{
	auto ModuloTwoPI = [=](float angle)
		{
			float a = angle;
			while (a < 0) a += 2.0f * 3.14159f;
			while (a >= 2.0f * 3.14159f) a -= 2.0f * 3.14159f;
			return a;
		};

	float tempx = sprite.x - player.x;
	float tempy = sprite.y - player.y;

	angle2player = ModuloTwoPI(atan2(tempx, tempy));
	float fAligneda = (2.0f * 3.14159f - player.rotationAngle) - 0.5f * 3.14159f;

	return abs(ModuloTwoPI(fAligneda + 3.14159f) - angle2player) < fov;
}

void force_powers::TKmove(Sprite& sprite, Player& player)
{
	sprite.x += player.movedifference.x;
	sprite.y += player.movedifference.y;

}

void force_powers::TKstrafe(Sprite& sprite, Player& player)
{
	sprite.x += player.stafedifference.x;
	sprite.y += player.stafedifference.y;
}

void force_powers::TKrotation(Sprite& sprite, Player& player)
{
	float differenceX = sprite.x - player.x;
	float differenceY = sprite.y - player.y;

	float distance = sqrtf(differenceX * differenceX + differenceY * differenceY);

	float angle_player_to_object = atan2f(differenceY, differenceX);

	float angle_difference = player.angledifference;



	sprite.x += distance * (cosf(angle_player_to_object + angle_difference) - cosf(angle_player_to_object));
	sprite.y += distance * (sinf(angle_player_to_object + angle_difference) - sinf(angle_player_to_object));
}

void force_powers::Draw(graphics& gfx, Texture& texture, int textureid)
{



	int textureWidth = upng_get_width(texture.characterTextures[textureid]);
	int textureHeight = upng_get_height(texture.characterTextures[textureid]);

	Vec2 pos = Vec2(WINDOW_WIDTH / 2, 30);

	for (int x = 0; x < textureWidth; x++)
	{
		for (int y = 0; y < textureHeight; y++)
		{
			int texturex = pos.x + x;
			int texturey = pos.y + y;

			color_t* spriteTextureBuffer = (color_t*)upng_get_buffer(texture.characterTextures[textureid]);
			color_t texelcolor = spriteTextureBuffer[(textureWidth * y) + x];
			if(texelcolor != 0xffff00ff)
			gfx.drawPixel(texturex, texturey, texelcolor);
		}
	}




}
