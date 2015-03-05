#include "TileManager.h"
#include "include\IL\il.h"
#include "include\IL\ilu.h"
#include "include\IL\ilut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"

#define CHUNK_WIDTH 22
#define MAP_WIDTH_IN_CHUNKS 15

TileManager::TileManager()
{
	numOfTiles = 0;
	//texID = ilLoadImage("assets/pokemon_sprites.png");
	texID = ilutGLLoadImage("assets/map_sprites.png");
	
	texW = ilGetInteger(IL_IMAGE_WIDTH);
	texH = ilGetInteger(IL_IMAGE_HEIGHT);
	std::vector<Tile*> tilePushBackVector;
	chunkVector.push_back(tilePushBackVector);
	mWidth = mHeight = 0;
	//Tile* tilePushBackTile = new Tile(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, texID, texW, texH);
	//chunkVector[0].push_back(tilePushBackTile);
}

void TileManager::SetSize(int w, int h)
{
	mWidth = w;
	mHeight = h;
}

void TileManager::CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid)
{
	int chunkNum = (int)((yPos/height) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((xPos/width) / CHUNK_WIDTH);
	if (chunkNum >= chunkVector.size())
	{
		std::vector<Tile*> tilePushBackVector;
		chunkVector.push_back(tilePushBackVector);
		Tile* tilePushBackTile = new Tile(0.f, 0.f, 16.f, 16.f, 0.f, 0.f, true, texID, texW, texH);
		for (int i = chunkVector.size(); chunkNum >= i; i++)
			chunkVector.push_back(tilePushBackVector);
	}

	std::vector<Tile*>* tileVector = &chunkVector[chunkNum];
	Tile* tmpTile = new Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH);
	tmpTile->ForceTexID(texID);
	tileVector->push_back(tmpTile);
	numOfTiles++;
	//printf("%i\n", numOfTiles);
}

void TileManager::CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int mapTransitionID)
{
	int chunkNum = (int)((yPos / height) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((xPos / width) / CHUNK_WIDTH);
	if (chunkNum >= chunkVector.size())
	{
		std::vector<Tile*> tilePushBackVector;
		chunkVector.push_back(tilePushBackVector);
		Tile* tilePushBackTile = new Tile(0.f, 0.f, 16.f, 16.f, 0.f, 0.f, true, texID, texW, texH);
		for (int i = chunkVector.size(); chunkNum >= i; i++)
			chunkVector.push_back(tilePushBackVector);
	}

	std::vector<Tile*>* tileVector = &chunkVector[chunkNum];
	Tile* tmpTile = new Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH);
//	tmpTile->MakePortal(mapTransitionID);
	tmpTile->ForceTexID(texID);
	tileVector->push_back(tmpTile);
	chunkVector.at(chunkNum).back()->MakePortal(mapTransitionID);
	numOfTiles++;
	//printf("%i\n", numOfTiles);
}

void TileManager::Clear()
{
	chunkVector.clear();
	chunkVector.shrink_to_fit();
}

void TileManager::RemoveTile(float x, float y)
{
	int chunkNum = (int)(y / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)(x / CHUNK_WIDTH);
	int tileNum = y - (int)(y / CHUNK_WIDTH)*CHUNK_WIDTH + x - (int)(x / CHUNK_WIDTH)*CHUNK_WIDTH;
	std::vector<Tile*> tileVector = chunkVector[chunkNum];
	free(tileVector.at(tileNum));
	tileVector.erase(tileVector.begin() + tileNum);
	chunkVector.shrink_to_fit();
}

void TileManager::DrawScene(float cameraPosX, float cameraPosY)
{
	int chunkNum = (int)((cameraPosY/15) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((cameraPosX/15) / CHUNK_WIDTH);
	int chunkPosX = (int)cameraPosX/15 % CHUNK_WIDTH;
	int chunkPosY = (int)cameraPosY/15 % CHUNK_WIDTH;
	//printf("CHUNK %i: (%i,%i)\n", chunkNum, chunkPosX, chunkPosY);
	//DrawAll();
	//return;

	DrawChunk(chunkNum, cameraPosX, cameraPosY);

	if (chunkPosX >= 7.f && chunkPosX <= 8.f && chunkPosY >= 7.f && chunkPosX <= 8.f)
	{
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY);

		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY);

		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY);
	}
	else if (chunkPosX <= 8.f && chunkPosY <= 8.f)
	{
		//bottom left
		//printf("bl\n");
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY);
	}
	else if (chunkPosX >= 7.f && chunkPosY <= 8.f)
	{
		//bottom right
		//printf("br\n");
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY);
	}
	else if (chunkPosX <= 8.f && chunkPosY >= 7.f)
	{
		//top left
		//printf("tl\n");
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY);
	}
	else if (chunkPosX >= 7.f && chunkPosY >= 7.f)
	{
		//top right
		//printf("tr\n");
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY);
	}
	else
		printf("ERROR: Invalid camera position at inner chunk coordinates (%i,%i)\n", chunkPosX, chunkPosY);
}

void TileManager::DrawChunk(int chunkNum, float cameraPosX, float cameraPosY)
{
	if (chunkNum >= 0 && chunkNum < chunkVector.size())
	{
		std::vector<Tile*> tileVector = chunkVector[chunkNum];
		for (int i = 0, s = chunkVector[chunkNum].size(); i < s; ++i)
		{
			tileVector.at(i)->Draw(cameraPosX, cameraPosY);
		}
	}
}

int TileManager::GetTexID()
{
	return chunkVector.at(0).at(0)->GetTexID();
}

void TileManager::DrawAll()
{
	for (int i = 0, s = chunkVector.size(); i < s; i++)
	{
		for (int j = 0, t = chunkVector[i].size(); j < t; j++)
			chunkVector[i][j]->Draw(0, 0);
	}
}

RECT TileManager::GetTileRect(int x, int y)
{
	int chunkNum = (y / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (x / CHUNK_WIDTH);
	int chunkPos = (x % CHUNK_WIDTH) + (y % MAP_WIDTH_IN_CHUNKS * CHUNK_WIDTH);
	
	return chunkVector.at(chunkNum).at(chunkPos)->GetRect();
}

bool TileManager::GetColision(int x, int y)
{
	int chunkNum = (int)(y / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)(x / CHUNK_WIDTH);
	int chunkPos = (x % CHUNK_WIDTH) + (y % MAP_WIDTH_IN_CHUNKS * CHUNK_WIDTH);
	if (chunkVector.at(chunkNum).size() > chunkPos)
		return chunkVector.at(chunkNum).at(chunkPos)->GetColision();
	else
		return false;
}

int TileManager::GetSize()
{
	return chunkVector.size() * chunkVector[0].size();
}

void TileManager::GetVars(int *chunkW, int *mapW, std::vector<std::vector<Tile*>>* chunkVectorPtr)
{
	*chunkW = CHUNK_WIDTH;
	*mapW = MAP_WIDTH_IN_CHUNKS;
	chunkVectorPtr = &chunkVector;
}

std::vector<std::vector<Tile*>>* TileManager::GetChunkVectorPtr()
{
	return &chunkVector;
}