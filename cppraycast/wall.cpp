#include "wall.h"

void Wall::changeColorIntensity(color_t* color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void Wall::renderWallProjection(graphics& gfx, Rays& ray, Player& player, Texture& texture)
{

	for (int x = 0; x < NUM_RAYS; x++) {

        // container for delayed pixel rendering
        std::vector<DelayedPixel> vDelayedPixels;
        // iterate the hitpoints until a non transparent wall is encountered
        bool bFinished = false;
        for (int i = 0; i < (int)ray.rays[x].size() && !bFinished; i++) {

            // get the distance to the hitpoint from the hit record info, and compensate for the view angle
            float prepDistance = ray.rays[x][i].distance * cos(ray.rays[x][i].rayAngle - player.rotationAngle);
            // calculate wall height from the distance
            float WallHeight = (TILE_SIZE / prepDistance * Dist_PROJ_PLANE);
            // project the wall top and bottom on the screen
            int wallStripHeight = (int)WallHeight;
            int wallTopY        = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
            int wallBottomY     = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
            // clip against windows boundaries
            wallTopY    = wallTopY    <             0 ?             0 : wallTopY;
            wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;

            int nHalfWindowHeight = WINDOW_HEIGHT / 2;
            float fPlayerH        = TILE_SIZE / 2.0f;
            float fFoV            = 60.0f;
            float fAngleStep      = fFoV / (float)NUM_RAYS;
            float fViewAngle      = (float)(x - (NUM_RAYS / 2)) * fAngleStep;
            float fCurAngle       = (player.rotationAngle * 180.0f / PI) + fViewAngle;
            float fPlayerX        = player.x;
            float fPlayerY        = player.y;
            float fCosCurAngle    = cos(fCurAngle  * PI / 180.0f);
            float fSinCurAngle    = sin(fCurAngle  * PI / 180.0f);
            float fCosViewAngle   = cos(fViewAngle * PI / 180.0f);

            int textureOffSetX;
            if (ray.rays[x][i].wasHitVertical) {
                textureOffSetX = (int)ray.rays[x][i].wallHitY % TILE_SIZE;
            }
            else {
                textureOffSetX = (int)ray.rays[x][i].wallHitX % TILE_SIZE;
            }

            //get correct texture id for map content
            int texNum = ray.rays[x][i].texture - 1;

            int texture_width  = upng_get_width( texture.textures[texNum]);
            int texture_height = upng_get_height(texture.textures[texNum]);

            // render this slice of the screen
            for (int y = 0; y < WINDOW_HEIGHT; y++)
            {
                if (y < wallTopY)         // pixel is above the wall, render sky color
                {
                    gfx.drawPixel(x, y, 0xff444444);
                }
                else if (y > wallBottomY)  // pixel is below the wall, render floor pixel
                {

                    float fFloorProjDistance = ((fPlayerH / (float)(y - nHalfWindowHeight)) * Dist_PROJ_PLANE) / fCosViewAngle;
                    float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
                    float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
                    int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
                    int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
                    color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[5]);
                    color_t texelColor = wallTextureBuffer[(nSampleY * texture_width) + nSampleX];

                    gfx.drawPixel(x, y, texelColor);
                }
                else                      // pixel is part of the wall, render wall pixel
                {
                    int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
                    int textureOffSetY = distanceFromTop * ((float)texture_height / wallStripHeight);

                    color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[texNum]);
                    color_t texelColor = wallTextureBuffer[(texture_width * textureOffSetY) + textureOffSetX];

                    if (ray.rays[x][i].wasHitVertical)
                    {
                        changeColorIntensity(&texelColor, 0.7);
                    }

                    // if the current wall/texture is transparent, then store pixel for delayed rendering
                    if (texture.isTransparent[texNum]) {
                        vDelayedPixels.push_back( { x, y, texelColor } );

                    } else {
                        gfx.drawPixel(x, y, texelColor);
                        bFinished = true;
                    }
                }
            }
            // quit rendering if the last processed hitpoint produces a non-transparent pixel
            bFinished = !texture.isTransparent[texNum];
        }

        // do the delayed rendering here
        for (int i = (int)vDelayedPixels.size() - 1; i >= 0; i--) {
            DelayedPixel &dp = vDelayedPixels[i];
            if (dp.p != 0x00000000) {
                gfx.drawPixel( dp.x, dp.y, dp.p );
            }
        }
	}
}


