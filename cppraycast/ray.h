#ifndef RAY_H
#define RAY_H
#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "player.h"
#include <float.h>
#include "utils.h"
#include <vector>




typedef struct {
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;

	// multilevel attempt
	
	int wallcount;
	//end
	bool wasHitVertical;
	bool firstwall;
	int texture;


}ray_t;

typedef struct
{
	float wallHitX;
	float wallHitY;
	float distance;
	int height;
	//std::vector<IntersectInfo> allHits;
}IntersectInfo;


extern ray_t rays[NUM_RAYS];
//extern std::vector<IntersectInfo> allHits;



void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderMapRays(void);
bool allHitPoints(float xintercept, float yintercept, float xstep, float ystep, std::vector<IntersectInfo>& hitlist);


#endif

