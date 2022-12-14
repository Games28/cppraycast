#include "player.h"


player_t player = {

	WINDOW_WIDTH / 2,
	WINDOW_HEIGHT / 2,
	1,
	 1,
	 0,
	 0,
	 PI / 2,
	100,
	45 * (PI / 180),
	 0,
	45 * (PI / 180),
	 0
};

void movePlayer(float deltaTime) {
	player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
	normalizeAngle(&player.rotationAngle);

	float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

	//wall collision
	if (!mapHasWallAt(newPlayerX, newPlayerY)) {
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

void renderMapPlayer(void) {

	drawRect(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR,
		0x0000ffff
	);



}


