#include "MapLoader.h"
#define MAP_BASE_SAVE_FILE "assets/maps.png"
#define TERRAIN_SPRITE_SHEET "assets/map_sprites.png"

//Rect mapSprites = MAP_ID_1_POSITION
#define MAP_ID_1_POSITION {0.f,0.f,351.f,30.f}
#define MAP_ID_0_POSITION {0.f,30.f,16.f,46.f}


struct Rect
{
	float x, y, w, h;
};

void MapLoader::freeTexture()
{
	if (TextureID != 0)
	{ 
		glDeleteTextures(1, &TextureID);
		TextureID = 0;
	}

	if (Pixels != NULL)
	{
		delete[] Pixels;
		Pixels = NULL;
	}
}

MapLoader::MapLoader(TileManager* tileMan, EntityManager* entityMan)
{
	TextureID = 0;
	Pixels = NULL;
	tileManager = tileMan;
	entityManager = entityMan;
	mapLoaded = false;
}

MapLoader::~MapLoader()
{
	freeTexture();
}



bool MapLoader::LoadMap(int mapID)
{
	Rect mapData;
	switch (mapID)
	{
	case 0: mapData = MAP_ID_0_POSITION; break;
	case 1: mapData = MAP_ID_1_POSITION; break;
	default:
		printf("ERROR: Invalid map id %i\n", mapID);
		return false;
	}

	bool pixelsloaded = false;
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(MAP_BASE_SAVE_FILE);

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			int size = mapData.w * mapData.h;
			Pixels = new ILubyte[size*4];
			ilCopyPixels(mapData.x, mapData.y, 0, mapData.w, mapData.h, 1, IL_RGB, IL_UNSIGNED_BYTE, Pixels);
			pixelsloaded = true;
		}
		ilDeleteImages(1, &imgID);
	}

	if (!pixelsloaded)
	{
		printf("ERROR: Unable to load base map image %s\n", MAP_BASE_SAVE_FILE);
		return false;
	}

	//Wipe current map data
	if (mapLoaded)
	{
		tileManager->Clear();
		entityManager->Clear();
	}
	else
		entityManager->CreateEntity(PLAYER, 0, 0);
	float done = 0;
	float progress = 0;
	GLuint size = mapData.w * mapData.h;
	tileManager->SetSize(mapData.w, mapData.h);
	for (int y = 0; y < mapData.h; y++)
	{
		for (int x = 0; x < mapData.w; x++)
		{

			int pos = x + y * mapData.w;
			#include "assets/maploader.txt"
			done++;
			progress = (done / size) * 100;
			
			//printf("Loading Map: %f\n", progress);
		}
	}
	//next step is to create and fill the vbo
	return true;
}

void RenderBackground()
{

}

void Scroll(float x, float y)
{

}