#include "ray.h"

ray_t rays[NUM_RAYS];
//std::vector<IntersectInfo> allHits;



void castRay(float rayAngle, int stripId) {
	normalizeAngle(&rayAngle);
	//turn in to functions bool below
	int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection

	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;
	
	// Increment xstep and ystep until we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
		
		if (mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			
				horzWallHitX = nextHorzTouchX;
				horzWallHitY = nextHorzTouchY;
				horzWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
				foundHorzWallHit = true;
			
			
			break;
		}
		else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	//allHitPoints(xintercept, yintercept, xstep, ystep, rays[stripId].);
	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	float e = tan(rayAngle);
	float a = xintercept - player.x;
	float b = a * e;
	float c = player.y + b;
	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	
	// Increment xstep and ystep until we find a wall
	while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;
		
		if (mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			
			
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;
				vertWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
				foundVertWallHit = true;
			
			
			break;
		}
		else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}
	//allHitPoints(xintercept, yintercept, xstep, ystep, allHits);
	// Calculate both horizontal and vertical hit distances and choose the smallest one
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;
	//multlevel attempt
	
	//end
	if (vertHitDistance < horzHitDistance) {
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].texture = vertWallContent;
		rays[stripId].wasHitVertical = true;
		rays[stripId].rayAngle = rayAngle;
	}
	else {
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].texture = horzWallContent;
		rays[stripId].wasHitVertical = false;
		rays[stripId].rayAngle = rayAngle;
	}
}


void castAllRays(void) {

	for (int col = 0; col < NUM_RAYS; col++) {

		//float rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / Dist_PROJ_PLANE);
		float rayAngle = player.rotationAngle + (col - NUM_RAYS / 2) / (float)(NUM_RAYS)*FOV_ANGLE;
		castRay(rayAngle, col);


	}

}

void renderMapRays(void) {

	for (int i = 0; i < NUM_RAYS; i++) {
		drawLine(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF00FF00
		);

	}
}

bool allHitPoints(float xintercept, float yintercept, float xstep, float ystep, std::vector<IntersectInfo>& hitlist)
{
	float touchx = xintercept;
	float touchy = yintercept;
	
	while (isInsideMap(touchx, touchy)) {
		
		if (mapHasWallAt(touchx, touchy)) {
			// found a wall hit
	
	
			IntersectInfo info;
			info.distance = distanceBetweenPoints(player.x, player.y, touchx, touchy);
			info.wallHitX = touchx;
			info.wallHitY = touchy;
			info.height = getMapAt((int)floor(touchx / TILE_SIZE), (int)floor(touchy / TILE_SIZE));
			hitlist.push_back(info);
			touchx += xstep;
			touchy += ystep;
			
	
	
			
		}
		else {
			touchx += xstep;
			touchy += ystep;
		}
	}
	return (hitlist.size() > 0);

}
