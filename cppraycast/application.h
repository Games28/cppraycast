#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>

#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "textures.h"
#include "wall.h"
#include "sprite.h"
#include "physics.h"
#include "Vec2.h"
//#include "force_powers.h"


class Application
{
public:
	bool isGameRunning = false;
	int ticksLastFrame = 0;

	//objects
	graphics graphic;
	Map map;
	Player player;
	Rays ray;
	Texture texture;
	Wall wall;
	Sprites sprite;
	thePhysics phs;
	//force_powers fp;

public:

	Application() = default;
     void setup();

	void processInput();

	void update();

	void render();
	void releaseResources();
};

#endif // !APPLICATION_H


