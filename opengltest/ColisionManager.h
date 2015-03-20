#ifndef COLISIONMANAGER_H
#define COLISIONMANAGER_H

#include "EntityManager.h"
#include "TileManager.h"
#include "ProjectileManager.h"
#include "MapLoader.h"

struct Portal
{
	int chunkNum;
	int colisionPos;
	int mapTransitionID;
	RECT pos;
};

class ColisionManager
{
public:
	ColisionManager(MapLoader* mapLoader);
	void RebuildColisionMap();
	void Update();

private:
	void UpdateChunk(int chunkNum, int entityIter);
	bool CheckAxis(RECT entPos, RotatedRectangle rRect, POINT axis);
	POINT GetMinMax(POINT proj[4], POINT axis);
	EntityManager* entityManager;
	TileManager* tileManager;
	ProjectileManager* projectileManager;
	MapLoader* mapLoader;
	
	int chunkW, mapW;
	std::vector<std::vector<Tile*>>* chunkVectorPtr;
	std::vector<Projectile*>* projectileVectorPtr;
	std::vector<std::vector<RECT>> colisionMap;
	std::vector<Portal> portalMap;
	std::vector<Item*> droppedItems;
	
};

#endif
