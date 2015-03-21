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
	for (int i = entityVector.size() - 1; i >= 0; i--)
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
	entitytype t = entityVector[index]->GetType();
	float val = (float)rand() / RAND_MAX;
	DroppedItem di;
	di.pickup.bottom = entityVector[index]->getY();
	di.pickup.top = entityVector[index]->getY() + 8;
	di.pickup.left = entityVector[index]->getX();
	di.pickup.right = entityVector[index]->getX() + 8;
	di.drop = new Sprite;
	di.drop->setPosition(di.pickup.left, di.pickup.bottom);
	di.drop->setSpriteFrameSize(8, 8);
	di.drop->setNumberOfAnimations(1);
	di.drop->setCurrentAnimation(0);
	di.drop->sheet = Item::itemSheet->sheet;
	if (t == ENEMY)
	{
		if (val < 0.15)
		{
			di.itemId = 0;
			di.qual = 1;
			di.drop->addSpriteAnimFrame(0, 0, 0);
			droppedItems.push_back(di);
		}	
	}
	else if (t == ELITE)
	{
		if (val < 0.5)
		{
			di.itemId = 0;
			di.qual = 1;
			di.drop->addSpriteAnimFrame(0, 0, 0);
			droppedItems.push_back(di);
		}
	}

	free(entityVector[index]);
	entityVector.erase(entityVector.begin() + index);
	entityVector.shrink_to_fit();
	for (int i = entityVector.size() - 1; i > 0; i--)
		entityVector.at(i)->UpdateIndex(i);
	score += 100;
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
	for (int i = 0, size = droppedItems.size(); i < size; i++)
		droppedItems[i].drop->draw(1.f);
	printf("DroppedItems: %i\n", droppedItems.size());
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

void EntityManager::GiveItem(int entNum, int itemId)
{
	entityVector[entNum]->GiveItem(itemId);
}