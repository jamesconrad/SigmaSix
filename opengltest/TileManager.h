#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include "Tile.h"
#include <vector>

enum tiletype{
	STATIC,
	NON_STATIC
};

class TileManager
{
public:
	TileManager();
	void CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid);
	void RemoveTile(float x, float y);
	void DrawScene(float cameraPosX, float cameraPosY);
	void DrawChunk(int chunkNum, float cameraPosX, float cameraPosY);
	void DrawAll();
	void SetSize(int w, int h);
	RECT GetTileRect(int x, int y);
	bool GetColision(int x, int y);
	int GetSize();
	void GetVars(int* chunkW, int* mapW, std::vector<std::vector<Tile*>>* chunkVectorPtr);
	std::vector<std::vector<Tile*>>* TileManager::GetChunkVectorPtr();

private:
	int GetTexID();
	std::vector<std::vector<Tile*>> chunkVector;
	std::vector<std::vector<Tile*>> tileVectorIter;
	bool empty;
	int texID, texW, texH, mWidth, mHeight;
	int numOfTiles;
};

#endif