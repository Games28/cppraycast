#ifndef MAP_H
#define MAP_H
#include "defs.h"

#include "graphics.h"




//static const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

bool mapHasWallAt(float x, float y);
bool isInsideMap(float x, float y);

void renderMapGrid(void);
int getMapAt(int i, int j);
#endif // !MAP_H

