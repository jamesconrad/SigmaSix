#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

extern int score;

struct DroppedItem
{
	RECT pickup;
	Sprite* drop;
	int qual;
	int itemId;
};

class EntityManager
{
public:
	static EntityManager* instance()
	{
		static EntityManager *instance = new EntityManager();
		return instance;
	}
	void CreateEntity(entitytype entityType, float x, float y);
	void DeleteEntity(int entityID);
	void Update(float dTime);
	void HandleInput(char key, bool press);
	void DrawAll(float x, float y);
	void DamageID(int id, float damage) { entityVector[id]->Damage(damage); }
	float getXofID(int id) { return entityVector[id]->getX(); }
	float getYofID(int id) { return entityVector[id]->getY(); }
	float getCXofID(int id) { return entityVector[id]->getCX(); }
	float getCYofID(int id) { return entityVector[id]->getCY(); }
	int getHP(int id) { return entityVector[id]->getHP(); }
	int getMaxHP(int id) { return entityVector[id]->getMaxHP(); }
	int getEnergy(int id) { return entityVector[id]->getEnergy(); }
	int getMaxEnergy(int id) { return entityVector[id]->getMaxEnergy(); }
	int GetSize() { return entityVector.size(); }
	entitytype GetType(int i) { return entityVector[i]->GetType(); }
	RECT getRectOfID(int id) 
	{ 
		if (id < (signed)entityVector.size()) return entityVector[id]->getRect();
		else return entityVector[0]->getRect();
	}
	void ModPosOfID(int id, vec2 mod);
	float SpeedOfID(int id) { return entityVector[id]->getSpeed(); }
	void FreezeID(int id, bool status) { entityVector[id]->Freeze(status); }
	void Clear();
	void OnHit(int id) { if (id < (signed)entityVector.size()) entityVector[id]->OnHit(); }

	//virtual void cancelMovement();
	void bcastRecv(char msg, int sender);
	void bcastSend();

	void GiveItem(int entNum, int itemId);

	std::vector<DroppedItem*> droppedItems;
	std::vector<Entity*> entityVector;
private:
	EntityManager();
	Sprite* entBarSprite;
	std::vector<Entity*> entityVecotrIter;
	std::vector<bcast> broadcast;
	ProjectileManager* projectileManager;
	SpriteSheetInfo barTexID;
	bool playerLoaded;

};

#endif