#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	projSheet = new Sprite();
	projSheet->loadSpriteSheet("assets/projectiles.png");
	texID = projSheet->sheet.textureID;
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
	Projectile *newProjectile = new Projectile(projectileVector.size(), texID, startX, startY, dirX, dirY, dmg, maxDur, projSpeed, projNum, ownerIndex);
	projectileVector.push_back(newProjectile);
}

void ProjectileManager::RemoveProjectile(int index)
{
	free(projectileVector[index]);
	projectileVector.erase(projectileVector.begin() + index);
	projectileVector.shrink_to_fit();
}

void ProjectileManager::Update(float dTime)
{
	std::vector<int> indiciesToRemove;
	for (int i = 0, s = projectileVector.size(); i < s; i++)
	{
		if (projectileVector[i] != __nullptr && projectileVector[i]->Update(dTime))
			indiciesToRemove.push_back(i);
	}

	for (int s = indiciesToRemove.size() - 1; s > 0; s--)
	{
		free(projectileVector[s]);
		projectileVector.erase(projectileVector.begin() + indiciesToRemove[s]);
		indiciesToRemove.pop_back();
	}
	projectileVector.shrink_to_fit();
}

void ProjectileManager::Draw()
{
	for (int i = 0, s = projectileVector.size(); i < s; i++)
		projectileVector[i]->Draw();
}