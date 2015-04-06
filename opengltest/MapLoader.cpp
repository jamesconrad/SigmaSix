#include "MapLoader.h"
#include "Dialog.h"
#include "ScriptReader.h"

#define MAP_BASE_SAVE_FILE "assets/level_maps.png"
#define TERRAIN_SPRITE_SHEET "assets/map_sprites.png"

//Rect mapSprites = MAP_ID_1_POSITION
#define MAP_ID_0_POSITION {120,0,16,16} //HUB

#define MAP_ID_1_POSITION {0,20,37,57} //Level 1 (Volcano level)
#define MAP_ID_11_POSITION {0,0,19,19} //Level 1 Boss

#define MAP_ID_2_POSITION {38,26,50,51} //Level 2 (Autumn level)
#define MAP_ID_12_POSITION {20,0,19,19} //Level 2 Boss

#define MAP_ID_3_POSITION {89,28,47,49} //Level 3 (Desert level)
#define MAP_ID_13_POSITION {40,0,19,19} //Level 3 Boss

#define MAP_ID_4_POSITION {137,21,35,56} //Level 4 (Field level)
#define MAP_ID_14_POSITION {60,0,19,19} //Level 4 Boss

#define MAP_ID_5_POSITION {173,21,35,56} //Level 5 (Tech level)
#define MAP_ID_15_POSITION {80,0,19,19} //Level 5 Boss

#define MAP_ID_6_POSITION {209,23,45,54} //Level 6 (Castle level)
#define MAP_ID_16_POSITION {100,0,19,19} //Level 6 Boss

#define MAP_ID_7_POSITION {255,46,15,31} //Tutorial

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

MapLoader::MapLoader()
{
	TextureID = 0;
	Pixels = NULL;
	tileManager = TileManager::instance();
	entityManager = EntityManager::instance();
	mapLoaded = false;
}

bool MapLoader::LoadMap(int mapID)
{
	Rect mapData;
	switch (mapID)
	{
	case 0: mapData = MAP_ID_0_POSITION; break;
	case 1: mapData = MAP_ID_1_POSITION; break;
	case 2: mapData = MAP_ID_2_POSITION; break;
	case 3: mapData = MAP_ID_3_POSITION; break;
	case 4: mapData = MAP_ID_4_POSITION; break;
	case 5: mapData = MAP_ID_5_POSITION; break;
	case 6: mapData = MAP_ID_6_POSITION; break;
	case 7: mapData = MAP_ID_7_POSITION; break;
	case 11: mapData = MAP_ID_11_POSITION; break;
	case 12: mapData = MAP_ID_12_POSITION; break;
	case 13: mapData = MAP_ID_13_POSITION; break;
	case 14: mapData = MAP_ID_14_POSITION; break;
	case 15: mapData = MAP_ID_15_POSITION; break;
	case 16: mapData = MAP_ID_16_POSITION; break;
	default:
		printf("ERROR: Invalid map id %i\n", mapID);
		return false;
	}

	currentMap = mapID;
	std::string filepath;
	filepath.append("assets/audio/map_");
	char mapnum[8];
	_itoa_s(mapID, mapnum, 10);
	filepath.append(mapnum);
	filepath.append(".mp3");
	SoundSystemClass::instance()->PlayBackground((char *)filepath.c_str());

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
	for (int y = mapData.h; y >= 0 ; y--)
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

	EntityManager::instance()->Update(0);

	if (mapID > 10)
	{
		entitytype et;
		switch (mapID)
		{
		case 11: et = F1; break;
		case 12: et = F2; break;
		case 13: et = F3; break;
		case 14: et = F4; break;
		case 15: et = F5; break;
		case 16: et = F6; break;
		}
		Dialog::instance()->Say(et, -1);
	}
	else if (mapID == 0 && !hubIntro)
	{
		Dialog::instance()->Say(NEUTRAL2, 0);
		hubIntro = true;
	}


	printf("%i",mapID);
	mapLoaded = true;
	return true;
}

void RenderBackground()
{

}

void Scroll(float x, float y)
{

}