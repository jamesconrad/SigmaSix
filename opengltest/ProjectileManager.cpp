#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	projSheet = new Sprite();
	projSheet->loadSpriteSheet("assets/projectiles.png");
	/*mySprite = new Sprite();
	mySprite->sheet.textureID = texID;
	mySprite->sheet.width = texW;
	mySprite->sheet.height = texH;
	mySprite->setNumberOfAnimations(1);
	mySprite->setPosition(xPos, yPos);
	mySprite->setSpriteFrameSize(width, height);
	mySprite->addSpriteAnimFrame(0, texX + 1.f, texY);
	mySprite->setLayerID(3);*/
}

void ProjectileManager::CreateProjectile(int projNum, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int ownerIndex)
{
	Projectile *newProjectile = new Projectile(projectileVector.size(), projSheet->sheet, startX, startY, dirX, dirY, dmg, maxDur, projSpeed, projNum, ownerIndex);
	projectileVector.push_back(newProjectile);
}

void ProjectileManager::RemoveProjectile(int index)
{
	//free(projectileVector[index]);
	projectileVector.erase(projectileVector.begin() + index);
	projectileVector.shrink_to_fit();
}

void ProjectileManager::Update(float dTime)
{
	std::vector<int> indiciesToRemove;
	for (int i =  projectileVector.size() - 1; i >= 0; i--)
	{
		if (projectileVector[i]->Update(dTime))
			RemoveProjectile(i);
	}
}

void ProjectileManager::Draw()
{
	for (int i = 0, s = projectileVector.size(); i < s; i++)
		projectileVector[i]->Draw();
}