#include "player.h"

void Player::initplayer( Map *mapPtr )
{
	x = WINDOW_WIDTH / 4;
	y = WINDOW_HEIGHT / 2;
	width = 2;
	height = 2;
	turnDirection = 0;
    walkDirection = 0;
	rotationAngle = PI / 2;
	walkSpeed = 100;
	turnSpeed = 45 * (PI / 180);
	strafeDirection = 0;
	isstrafingleft = true;
	isstrafingright = true;

	pMap = mapPtr;
}

void Player::movePlayer(float deltatime)
{
	anglebefore = rotationAngle;
	playermovebefore = Vec2(x,y);
	rotationAngle += turnDirection * turnSpeed * deltatime;
	normalizeAngle(&rotationAngle);
	angleaftere = rotationAngle;
	angledifference = angleaftere - anglebefore;
	float moveStep = walkDirection * walkSpeed * deltatime;

	float newPlayerX = x + cos(rotationAngle) * moveStep;
	float newPlayerY = y + sin(rotationAngle) * moveStep;

	//wall collision
	if (!pMap->mapHasWallAt(newPlayerX, newPlayerY)) {
		x = newPlayerX;
		y = newPlayerY;
		playermoveafter = Vec2(newPlayerX,newPlayerY);
	}
	movedifference = playermoveafter - playermovebefore;

}


void Player::strafePlayer(float deltatime)
{
	playerstrafebefore = Vec2(x, y);
	float strafestep = strafeDirection * walkSpeed * deltatime;
	float newStrafeX = 0;
	float newStrafeY = 0;
	if (isstrafingleft)
	{
		newStrafeX = x - sin(rotationAngle) * strafestep;
		newStrafeY = y + cos(rotationAngle) * strafestep;
	}
	if (isstrafingright)
	{
		newStrafeX = x + sin(rotationAngle) * strafestep;
		newStrafeY = y - cos(rotationAngle) * strafestep;
	}

	if (!pMap->mapHasWallAt(newStrafeX, newStrafeY))
	{
		x = newStrafeX;
		y = newStrafeY;
		Playerstrafeafter = Vec2(newStrafeX, newStrafeY);
	}
	stafedifference = Playerstrafeafter - playerstrafebefore;
}

void Player::renderMapPlayer(graphics& gfx)
{
	gfx.drawRect(
		x * MINIMAP_SCALE_FACTOR,
		y * MINIMAP_SCALE_FACTOR,
		width * MINIMAP_SCALE_FACTOR,
		height * MINIMAP_SCALE_FACTOR,
		0xffffffff
	);
}

void Player::normalizeAngle(float* angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0) {
		*angle = TWO_PI + *angle;
	}
}
