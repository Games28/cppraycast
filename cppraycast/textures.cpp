#include "textures.h"
#include <stdio.h>

upng_t* textures[NUM_TEXTURES];
static const char* textureFileNames[NUM_TEXTURES] = {
	"./images/redbrick.png",
	"./images/purplestone.png",
	"./images/mossystone.png",
	"./images/graystone.png",
	"./images/bluestone.png",
	"./images/colorstone.png",
	"./images/wood.png",
	"./images/eagle.png",
	"./images/pikuma.png",
	"./images/barrel_big.png",
	"./images/light.png",  //10
	"./images/table.png",  //11
	"./images/guard.png", //12
	"./images/armor.png" //13


};

void loadTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_t* upng = upng_new_from_file(textureFileNames[i]);
		if (upng != NULL) {
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK) {
				textures[i] = upng;
			}
			else
			{
				printf("error decoding texture file % s \n", textureFileNames[i]);
			}

		}
		else
		{
			printf("error loading texture %s \n", textures[i]);
		}
	}
}

void freeTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_free(textures[i]);
	}
}

