#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#ifndef BCAST_S
#define BCAST_S
struct bcast
{
	char msg;
	int sender;
};
#endif BCAST_S

enum entitytype {
	PLAYER,
	ENEMY,
	ELITE,
	NEUTRAL,
	BOSS,
	MINIBOSS
};

#include "Entity.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"



class EntityManager
{
public:
	EntityManager(ProjectileManager* projManager, SpriteSheetInfo bar);
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
	RECT getRectOfID(int id) { return entityVector[id]->getRect(); }
	void ModPosOfID(int id, vec2 mod);
	void Clear();

	//virtual void cancelMovement();
	void bcastRecv(char msg, int sender);
	void bcastSend();

private:
	std::vector<Entity*> entityVector;
	std::vector<Entity*> entityVecotrIter;
	std::vector<bcast> broadcast;
	ProjectileManager* projectileManager;
	SpriteSheetInfo barTexID;
	bool playerLoaded;

};

#endif