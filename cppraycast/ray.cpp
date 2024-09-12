#include <cfloat>
#include "ray.h"


void Rays::castRay(float rayAngle, int stripId, Player& player, Map& map)
{
    // make sure rayAngle is within 0 and 2 PI
	normalizeAngle( &rayAngle );

	// determine whether ray is going up or down
	int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	int isRayFacingUp = !isRayFacingDown;
    // determine whether ray is going left or right
	int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundHorzWallHit = false;
	float horzWallHitX    = 0;
	float horzWallHitY    = 0;
	int horzWallContent   = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection

	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft  && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// aux lambda to populate a hit record
    auto fill_hitrec = [=]( ray_t &rec, float fA, float fWhX, float fWhY, float fDst, bool bHitVer, int nTxtr ) {
        rec.rayAngle       = fA;
        rec.wallHitX       = fWhX;
        rec.wallHitY       = fWhY;
        rec.frontdistance       = fDst;
        rec.wasHitVertical = bHitVer;
        rec.texture        = nTxtr;
    };

	// clear the list of hit points before you start filling it again
    rays[stripId].clear();

	// Increment xstep and ystep until we find a non-transparent wall
	while (map.isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (map.mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map.getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
            float horzHitDistance = foundHorzWallHit
                ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
                : FLT_MAX;

            ray_t tmp_hitpoint;
            fill_hitrec( tmp_hitpoint, rayAngle, horzWallHitX, horzWallHitY, horzHitDistance, false, horzWallContent );
            rays[stripId].push_back( tmp_hitpoint );
		}
		nextHorzTouchX += xstep;
		nextHorzTouchY += ystep;
	}

	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundVertWallHit = false;
	float vertWallHitX    = 0;
	float vertWallHitY    = 0;
	int vertWallContent   = 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	float e = tan(rayAngle);
	float a = xintercept - player.x;
	float b = a * e;
	float c = player.y + b;
	yintercept = c;

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp   && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;


	// Increment xstep and ystep until we find a wall
	while (map.isInsideMap(nextVertTouchX, nextVertTouchY)) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (map.mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map.getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
            float vertHitDistance = foundVertWallHit
                ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
                : FLT_MAX;

            ray_t tmp_hitpoint;
            fill_hitrec( tmp_hitpoint, rayAngle, vertWallHitX, vertWallHitY, vertHitDistance, true, vertWallContent );
            rays[stripId].push_back( tmp_hitpoint );
		}
		nextVertTouchX += xstep;
		nextVertTouchY += ystep;
	}

    // sort list of hitpoints from close by to far away
    std::sort(
        rays[stripId].begin(),
        rays[stripId].end(),
        []( ray_t &a, ray_t &b ) {
            return a.frontdistance < b.frontdistance;
        }
    );
}

void Rays::castAllRays(Player& player, Map& map)
{
	for (int col = 0; col < NUM_RAYS; col++) {

		//float rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / Dist_PROJ_PLANE);
		float rayAngle = player.rotationAngle + (col - NUM_RAYS / 2) / (float)(NUM_RAYS)*FOV_ANGLE;
		castRay(rayAngle, col,player,map);
	}
}

void Rays::renderMapRays(graphics& gfx,Player& player)
{
	for (int i = 0; i < NUM_RAYS; i++) {
		gfx.drawLine(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i][0].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i][0].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF00FF00
		);
	}
}

void Rays::normalizeAngle(float* angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0) {
		*angle = TWO_PI + *angle;
	}
}

float Rays::distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
