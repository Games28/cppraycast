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



    for (int x = 0; x < NUM_RAYS; x++)
    {

        std::vector<DelayedPixel> vDelayedPixels;
        // iterate the hitpoints until a non transparent wall is encountered
        bool bFinished = false;
        int nHalfWindowHeight = (WINDOW_HEIGHT * player.fPlayerH) + (int)player.fLookUp;
        for (int i = 0; i < (int)ray.rays[x].size() && !bFinished; i++)
        {
           
            // get the distance to the hitpoint from the hit record info, and compensate for the view angle
            float prepDistance = ray.rays[x][i].distance * cos(ray.rays[x][i].rayAngle - player.rotationAngle);
            // calculate wall height from the distance
            float WallHeight = (TILE_SIZE / prepDistance * Dist_PROJ_PLANE);
            // project the wall top and bottom on the screen
            int wallStripHeight = (int)WallHeight;
            int wallTopY = (nHalfWindowHeight) - (wallStripHeight / 2);
            int wallBottomY = (nHalfWindowHeight) + (wallStripHeight / 2);
            // clip against windows boundaries

            
           wallTopY = wallTopY < 0 ? 0 : wallTopY;
            wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;

            
            float fPlayerH = (TILE_SIZE / 2);
            float fFoV = 60.0f;
            float fAngleStep = fFoV / (float)NUM_RAYS;
            float fViewAngle = (float)(x - (NUM_RAYS / 2)) * fAngleStep;
            float fCurAngle = (player.rotationAngle * 180.0f / PI) + fViewAngle;
            float fPlayerX = player.x;
            float fPlayerY = player.y;
            float fCosCurAngle = cos(fCurAngle * PI / 180.0f);
            float fSinCurAngle = sin(fCurAngle * PI / 180.0f);
            float fCosViewAngle = cos(fViewAngle * PI / 180.0f);

            int textureOffSetX;
            if (ray.rays[x][i].wasHitVertical) {
                textureOffSetX = (int)ray.rays[x][i].wallHitY % TILE_SIZE;
            }
            else {
                textureOffSetX = (int)ray.rays[x][i].wallHitX % TILE_SIZE;
            }

            //get correct texture id for map content
            int texNum = ray.rays[x][i].texture - 1;

           int texture_width = upng_get_width(texture.textures[texNum]);
           int texture_height = upng_get_height(texture.textures[texNum]);


            for (int y = 0; y < WINDOW_HEIGHT; y++)
            {
                if (y < nHalfWindowHeight)
                {
                    gfx.drawPixel(x, y, 0xff444444);
                }
                else
                {

                    float fFloorProjDistance = ((fPlayerH / (float)(y - nHalfWindowHeight )) * Dist_PROJ_PLANE) / fCosViewAngle;
                    float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
                    float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
                    int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
                    int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
                    color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[5]);
                    int texture_width = upng_get_width(texture.textures[5]);
                    int texture_height = upng_get_height(texture.textures[5]);
                    color_t texelColor = wallTextureBuffer[(nSampleY * texture_width) + nSampleX];

                    gfx.drawPixel(x, y, texelColor);
                }
            }

            for (int y = wallTopY; y < wallBottomY; y++)
            {
                int distanceFromTop = y + (wallStripHeight / 2) - (nHalfWindowHeight);
                int textureOffSetY = (distanceFromTop ) * ((float)texture_height / wallStripHeight);

                color_t* wallTextureBuffer = (color_t*)upng_get_buffer(texture.textures[texNum]);
                color_t texelColor = wallTextureBuffer[(texture_width * textureOffSetY) + textureOffSetX];

                if (ray.rays[x][i].wasHitVertical)
                {
                    changeColorIntensity(&texelColor, 0.7);
                }

                // if the current wall/texture is transparent, then store pixel for delayed rendering
                if (texture.isTransparent[texNum]) {
                    vDelayedPixels.push_back({ x, y, texelColor });

                }
                else {
                    gfx.drawPixel(x, y, texelColor);
                    bFinished = true;
                }

            }
            bFinished = !texture.isTransparent[texNum];
        }

        

        // do the delayed rendering here
        //for (int i = (int)vDelayedPixels.size() - 1; i >= 0; i--) {
        //    DelayedPixel& dp = vDelayedPixels[i];
        //    if (dp.p != 0x00000000) {
        //        gfx.drawPixel(dp.x, dp.y, dp.p);
        //    }
        //}
    }

	
   // iterate over all screen columns{
   // draw sky above the horizon
   // draw floor / ground below the horizon
   //
   // iterate over all hit points, which are supposed to be sorted from far away to close by {
   //
   //         // each hit point hits on a block, having a top and bottom value, 
   //         // both in world space and in (on screen) projected space.
   //         // These values are available at this point
   //
   //         if (player height > block top) { // note - world space!
   //
   //             // player's view point is above the top of the block, so roof is visible
   //             // (roof is just the top face of the block)
   //             render roof section for this block
   //         }
   //
   //         render wall section for this block
   //
   //         if (player height < block bottom) { // note - world space again!
   //             // player's view point is below the bottom of the block, so ceiling is visible
   //             // (ceiling is just the bottom face of the block)
   //             render ceiling for this block
   //         }
   //     }
   // }

   
}


