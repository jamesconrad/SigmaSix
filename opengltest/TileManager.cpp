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

void TileManager::CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int texSpacing, int numFrames, float animDelay)
{
	int chunkNum = (int)((yPos/height) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((xPos/width) / CHUNK_WIDTH);
	if (chunkNum >= (signed)chunkVector.size())
	{
		std::vector<Tile*> tilePushBackVector;
		chunkVector.push_back(tilePushBackVector);
		//CreateTile(STATIC, x * 15, (mapData.h - y) * 15, 16, 16, 136, 0, false);
		Tile* tilePushBackTile = new Tile(0, 0, 16, 16, 136, 0, false, texID, texW, texH);
		for (int i = chunkVector.size(); chunkNum >= i; i++)
			chunkVector.push_back(tilePushBackVector);
	}

	Tile* tmpTile;
	std::vector<Tile*>* tileVector = &chunkVector[chunkNum];
	if (tileType == STATIC)
		tmpTile = new Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH);
	else if (tileType == NON_STATIC)
		tmpTile = new AnimTile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH, texSpacing, numFrames, animDelay);
	tmpTile->ForceTexID(texID);
	tileVector->push_back(tmpTile);
	numOfTiles++;
	//printf("%i\n", numOfTiles);
}

void TileManager::CreatePortal(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int mapTransitionID, int texSpacing, int numFrames, float animDelay)
{
	int chunkNum = (int)((yPos / height) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((xPos / width) / CHUNK_WIDTH);
	if (chunkNum >= (signed)chunkVector.size())
	{
		std::vector<Tile*> tilePushBackVector;
		chunkVector.push_back(tilePushBackVector);
		//Tile* tilePushBackTile = new Tile(0, 0, 16, 16, 136, 0, true, texID, texW, texH);
		for (int i = chunkVector.size(); chunkNum >= i; i++)
			chunkVector.push_back(tilePushBackVector);
	}
	Tile* tmpTile;
	std::vector<Tile*>* tileVector = &chunkVector[chunkNum];
	if (tileType == STATIC)
		tmpTile = new Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH);
	else if (tileType == NON_STATIC)
		tmpTile = new AnimTile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH, texSpacing, numFrames, animDelay);
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

void TileManager::DrawScene(float cameraPosX, float cameraPosY, float dTime)
{
	int chunkNum = (int)((cameraPosY/15) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((cameraPosX/15) / CHUNK_WIDTH);
	int chunkPosX = (int)cameraPosX/15 % CHUNK_WIDTH;
	int chunkPosY = (int)cameraPosY/15 % CHUNK_WIDTH;
	//printf("CHUNK %i: (%i,%i)\n", chunkNum, chunkPosX, chunkPosY);
	//DrawAll();
	//return;

	DrawChunk(chunkNum, cameraPosX, cameraPosY, dTime);

	if (chunkPosX >= 10 && chunkPosX <= 11 && chunkPosY >= 10 && chunkPosX <= 11)
	{
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY, dTime);

		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY, dTime);

		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY, dTime);
	}
	else if (chunkPosX <= 11 && chunkPosY <= 10)
	{
		//bottom left
		//printf("bl\n");
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY, dTime);
	}
	else if (chunkPosX >= 10 && chunkPosY <= 11)
	{
		//bottom right
		//printf("br\n");
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY, dTime);
	}
	else if (chunkPosX <= 11 && chunkPosY >= 10)
	{
		//top left
		//printf("tl\n");
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS - 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum - 1, cameraPosX, cameraPosY, dTime);
	}
	else if (chunkPosX >= 10 && chunkPosY >= 10)
	{
		//top right
		//printf("tr\n");
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + MAP_WIDTH_IN_CHUNKS + 1, cameraPosX, cameraPosY, dTime);
		DrawChunk(chunkNum + 1, cameraPosX, cameraPosY, dTime);
	}
	else
		printf("ERROR: Invalid camera position at inner chunk coordinates (%i,%i)\n", chunkPosX, chunkPosY);
}

void TileManager::DrawChunk(int chunkNum, float cameraPosX, float cameraPosY, float dTime)
{
	if (chunkNum >= 0 && chunkNum < (signed)chunkVector.size())
	{
		std::vector<Tile*> tileVector = chunkVector[chunkNum];
		for (int i = 0, s = chunkVector[chunkNum].size(); i < s; ++i)
		{
			tileVector.at(i)->update(dTime);
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
	if ((signed)chunkVector.at(chunkNum).size() > chunkPos)
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

void TileManager::ReplaceTile(float rX, float rY, tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int texSpacing, int numFrames, float animDelay)
{
	int chunkNum = (int)((yPos / height) / CHUNK_WIDTH) * MAP_WIDTH_IN_CHUNKS + (int)((xPos / width) / CHUNK_WIDTH);
	int chunkPos = 0;

	for (int i = chunkVector.at(chunkNum).size() - 1; i >= 0; i--)
	{
		RECT tmp = chunkVector[chunkNum].at(i)->GetRect();
		if (tmp.left == rX && tmp.bottom == rY)
		{
			chunkPos = i;
			break;
		}
	}

	Tile* tmpTile;
	std::vector<Tile*>* tileVector = &chunkVector[chunkNum];
	if (tileType == STATIC)
		tmpTile = new Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH);
	else if (tileType == NON_STATIC)
		tmpTile = new AnimTile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH, texSpacing, numFrames, animDelay);
	tmpTile->ForceTexID(texID);
	free(chunkVector[chunkNum].at(chunkPos));
	chunkVector[chunkNum].at(chunkPos) = tmpTile;
}