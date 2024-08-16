#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>

#include "defs.h"
#include "upng.h"


class Texture
{
public:
	Texture() = default;

	upng_t* textures[NUM_TEXTURES];
	upng_t* characterTextures[NUM_CHARTEXTURES];

	// to determine whether a texture contains transparency
	bool bIsTransparent[NUM_TEXTURES];

	void loadTextures();
	void freeTextures();

public:
	const char* textureFileNames[NUM_TEXTURES] = {
        "./images/redbrick.png",                   //  0
        "./images/purplestone.png",                //  1
        "./images/mossystone.png",                 //  2
        "./images/graystone.png",                  //  3
        "./images/bluestone.png",                  //  4
        "./images/colorstone.png",                 //  5
        "./images/eagle.png",                      //  6
        "./images/redbrick_window.rbg.png",        //  7  <-- contains transparency
        "./images/redbrick_door.rbg.png",          //  8  <-- contains transparency
        "./images/wood.png",                       //  9
        "./images/light.png",                      // 10
        "./images/table.png",                      // 11
        "./images/guard.png",                      // 12
        "./images/armor.png"                       // 13
	};

	// to determine whether a texture contains transparency
	bool isTransparent[NUM_TEXTURES] = {
	    false,  //  0
	    false,  //  1
	    false,  //  2
	    false,  //  3
	    false,  //  4
	    false,  //  5
	    false,  //  6
	    true ,  //  7  <-- contains transparency
	    true ,  //  8  <-- contains transparency
	    false,  //  9
	    false,  // 10
	    false,  // 11
	    false,  // 12
	    false   // 13
	};

	const char* characterFileNames[NUM_CHARTEXTURES] = {
		"./images/newicon.png",
		"./images/newiconglow.png",
		"./images/r2d2ground.png",
		"./images/r2idletest.png",
		"./images/crate1x64.png",
		"./images/trooper.png",
		"./images/trooperT.png",
	};
};

#endif

