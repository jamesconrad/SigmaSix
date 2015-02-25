#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"
#include "TileManager.h"

class MapLoader
{
public:
	MapLoader(TileManager* tileManager);
	~MapLoader();

	bool LoadMap(int MapID);
	void RenderBackground();
	void Scroll(float x, float y);
	void freeTexture();
private:
	ILubyte *Pixels;
	GLuint TextureID;
	GLuint imageWidth, imageHeight, textureWidth, textureHeight;
	TileManager* tileManager;
};

#endif