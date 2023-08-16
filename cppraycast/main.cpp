#include <SDL.h>

#include "defs.h"
#include "wall.h"

#include "graphics.h"
#include "map.h"
#include "ray.h"
#include "player.h"
#include "sprite.h"







bool isGameRunning = false;
int ticksLastFrame = 0;


void setup() {

	//loading textures from texture.h
	loadTextures();
}


void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT: {
		isGameRunning = false;
		break;
	}
	case SDL_KEYDOWN: {
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = false;
		if (event.key.keysym.sym == SDLK_w)
			player.walkDirection = +1;
		if (event.key.keysym.sym == SDLK_s)
			player.walkDirection = -1;
		if (event.key.keysym.sym == SDLK_d)
			player.turnDirection = +1;
		if (event.key.keysym.sym == SDLK_a)
			player.turnDirection = -1;
		//if (event.key.keysym.sym == SDLK_UP)
		//	vertmove = -1.0f;
		//if (event.key.keysym.sym == SDLK_DOWN)
		//	vertmove = 1.0f;

		break;
	}
	case SDL_KEYUP: {
		if (event.key.keysym.sym == SDLK_w)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_s)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_d)
			player.turnDirection = 0;
		if (event.key.keysym.sym == SDLK_a)
			player.turnDirection = 0;
		//if (event.key.keysym.sym == SDLK_UP)
		//	vertmove = 0.0f;
		//if (event.key.keysym.sym == SDLK_DOWN)
		//	vertmove = 0.0f;

		break;
	}


	}
}

void update() {

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_LENGTH));


	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
}




void render() {

	clearColorBuffer(0xff000000);
	renderWallProjection();
	renderSpriteProjection();

	renderMapGrid();
	renderMapRays();
	renderMapSprites();
	renderMapPlayer();

	renderColorBuffer();

}

void releaseResources(void)
{
	freeTextures();
	destroyWindow();
}

int main(int argc, char* args[])
{
	isGameRunning = initializeWindow();

	setup();

	while (isGameRunning) {
		processInput();
		update();
		render();

	}

	releaseResources();

	return 0;
}