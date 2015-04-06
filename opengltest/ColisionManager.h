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
	static ColisionManager* instance()
	{
		static ColisionManager* instance = new ColisionManager();
		return instance;
	}
	void RebuildColisionMap();
	void Update();
	void DropItem(float x, float y, Item item);

private:
	ColisionManager();
	void UpdateChunk(int chunkNum, int entityIter);
	bool CheckAxis(RECT entPos, RotatedRectangle rRect, POINT axis);
	POINT GetMinMax(POINT proj[4], POINT axis);
	EntityManager* entityManager;
	TileManager* tileManager;
	ProjectileManager* projectileManager;
	MapLoader* mapLoader;
	
	int chunkW, mapW;
	int mapNum;
	std::vector<std::vector<Tile*>>* chunkVectorPtr;
	std::vector<Projectile*>* projectileVectorPtr;
	std::vector<std::vector<RECT>> colisionMap;
	std::vector<Portal> portalMap;
	
};

#endif
