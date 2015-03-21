#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "TileManager.h"
#include "EntityManager.h"
#include "SoundSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

class MapLoader
{
public:
	static MapLoader* instance()
	{
		static MapLoader* instance = new MapLoader();
		return instance;
	}
	bool LoadMap(int MapID);
	void RenderBackground();
	void Scroll(float x, float y);
	void freeTexture();
	int GetCurrentMap() { return currentMap; }
private:
	MapLoader();
	ILubyte *Pixels;
	GLuint TextureID;
	GLuint imageWidth, imageHeight, textureWidth, textureHeight;
	TileManager* tileManager;
	EntityManager* entityManager;
	bool mapLoaded;
	int currentMap;
};

#endif