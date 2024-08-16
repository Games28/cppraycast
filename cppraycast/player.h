#ifndef PLAYER_H
#define PLAYER_H
#include "graphics.h"
#include "map.h"
#include "defs.h"
#include "Vec2.h"

class Player
{
public:
	Player() = default;
	void initplayer( Map *mapPtr );
	void movePlayer(float deltatime);
	void strafePlayer(float deltatime);
	void renderMapPlayer(graphics& gfx);
	void normalizeAngle(float* angle);

public:
	float x;
	float y;
	float width;
	float height;
	int   turnDirection; // -1 for left, +1 for right
	int   walkDirection; // -1 for back, +1 for front
	int   strafeDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
	bool  isstrafingleft;
	bool  isstrafingright;

	Vec2 playermovebefore = Vec2(0, 0);
	Vec2 playermoveafter = Vec2(0, 0);
	Vec2 movedifference = Vec2(0, 0);
	float anglebefore = 0.0f;
	float angleaftere = 0.0f;
	float angledifference = 0.0f;

	Vec2 playerstrafebefore = Vec2(0, 0);
	Vec2 Playerstrafeafter = Vec2(0, 0);
	Vec2 stafedifference = Vec2(0, 0);

//	Map map;
	Map *pMap = nullptr;
};

#endif // !PLAYER_H



