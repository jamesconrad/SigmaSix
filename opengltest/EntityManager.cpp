#include "EntityManager.h"

EntityManager::EntityManager()
{
	entBarSprite = new Sprite;
	entBarSprite->loadSpriteSheet("assets/bars.png");
	barTexID.height = 24;
	barTexID.width = 120;
	barTexID.textureID = entBarSprite->GetTexID();

	projectileManager = ProjectileManager::instance();
	playerLoaded = false;
}

void EntityManager::Update(float dTime)
{
	for (int i = 0, size = entityVector.size(); i < size; i++)
		entityVector[i]->update(dTime);
	bcastSend();
}

void EntityManager::CreateEntity(entitytype entityType, float x, float y)
{
	if (entityType == PLAYER && !playerLoaded)
	{
		Player* newEntity = new Player(projectileManager, barTexID, x, y);
		entityVector.push_back(newEntity);
		playerLoaded = true;
	}
	else if (entityType == PLAYER && playerLoaded)
	{
		//just move the player
		float cx, cy;
		vec2 pos;
		cx = entityVector.at(0)->getX();
		cy = entityVector.at(0)->getY();
		pos.x = x - cx;
		pos.y = y - cy;
		entityVector.at(0)->ModPos(pos);
	}
	else
	{
		Enemy* newEntity = new Enemy(projectileManager, this, barTexID, x, y, entityVector.size(), entityType, entityVector.size());
		entityVector.push_back(newEntity);
	}
}

void EntityManager::DeleteEntity(int index)
{

}

void EntityManager::Clear()
{
	for (int i = entityVector.size() - 1; i > 0; i--)
		entityVector.erase(entityVector.begin() + i);
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

void EntityManager::bcastRecv(char msg, int sender)
{
	bcast tmp;
	tmp.msg = msg;
	tmp.sender = sender;
	broadcast.push_back(tmp);
}

void EntityManager::bcastSend()
{
	while (!broadcast.empty())
	{
		for (int ent = 1, s = entityVector.size(); ent < s; ent++)
			entityVector.at(ent)->bcastRecv(broadcast.back());
		broadcast.pop_back();
	}
}