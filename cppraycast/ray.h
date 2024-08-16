#ifndef RAY_H
#define RAY_H

#include <limits>
#include <vector>

#include "defs.h"
#include "player.h"
#include "map.h"
#include "graphics.h"
#include <algorithm>


struct ray_t
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	bool firstwall;
	int texture;
};

typedef std::vector<ray_t> HitListType;

class Rays
{
public:
	Rays() = default;
	void castRay(float rayAngle, int stripId, Player& player, Map& map);
	void castAllRays(Player& player, Map& map);
	void renderMapRays(graphics& gfx, Player& player);
	void normalizeAngle(float* angle);
	float distanceBetweenPoints(float x1, float y1, float x2, float y2);

public:
	HitListType rays[NUM_RAYS];
};

#endif // ifndef RAY_H



