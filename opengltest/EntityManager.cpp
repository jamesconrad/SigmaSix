#include "EntityManager.h"

EntityManager::EntityManager(ProjectileManager* projManager, SpriteSheetInfo bar)
{
	projectileManager = projManager;
	barTexID = bar;
}

void EntityManager::Update(float dTime)
{
	for (int i = 0, size = entityVector.size(); i < size; i++)
		entityVector[i]->update(dTime);
}

void EntityManager::CreateEntity(entitytype entityType)
{
	if (entityType == PLAYER)
	{
		Player* newEntity = new Player(projectileManager, barTexID);
		entityVector.push_back(newEntity);
	}
	else if (entityType == ENEMY)
	{
		Enemy* newEntity = new Enemy(projectileManager, this, barTexID);
		entityVector.push_back(newEntity);
	}
}

void EntityManager::HandleInput(char key, bool press)
{
	for (int i = 0, size = entityVector.size(); i < size; i++)
		entityVector[i]->handleinput(key, press);
}

void EntityManager::DrawAll(float x, float y)
{
	for (int i = 0, size = entityVector.size(); i < size; i++)
		entityVector[i]->draw();
}

void EntityManager::ModPosOfID(int id, vec2 mod)
{
	entityVector[id]->ModPos(mod);
}