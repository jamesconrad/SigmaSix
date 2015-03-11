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
	static TileManager* instance()
	{
		static TileManager *instance = new TileManager();
		return instance;
	}
	void CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid);
	void CreateTile(tiletype tileType, float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int mapTransitionID);
	void RemoveTile(float x, float y);
	void DrawScene(float cameraPosX, float cameraPosY);
	void DrawChunk(int chunkNum, float cameraPosX, float cameraPosY);
	void DrawAll();
	void SetSize(int w, int h);
	RECT GetTileRect(int x, int y);
	bool GetColision(int x, int y);
	int GetSize();
	void GetVars(int* chunkW, int* mapW, std::vector<std::vector<Tile*>>* chunkVectorPtr);
	void Clear();
	std::vector<std::vector<Tile*>>* TileManager::GetChunkVectorPtr();

private:
	TileManager();
	int GetTexID();
	std::vector<std::vector<Tile*>> chunkVector;
	std::vector<std::vector<Tile*>> tileVectorIter;
	std::vector<int> portalIndex;
	bool empty;
	int texID, texW, texH, mWidth, mHeight;
	int numOfTiles;
};

#endif