#ifndef PROJECTILE_H
#define PROJECTILE_H

#ifndef RRECT
#define RRECT
struct RotatedRectangle
{
	float maxX, minX, maxY, minY;
};
#endif

#include "Projectile.h"

class ProjectileManager
{
public:
	static ProjectileManager* instance()
	{
		static ProjectileManager *instance = new ProjectileManager();
		return instance;
	}
	void CreateProjectile(int projNum, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int ownerIndex);
	void RemoveProjectile(int index);
	void Update(float dTime);
	void Draw();
	std::vector<Projectile*>* GetProjectileVector() { return &projectileVector; }
	float DamageOfID(int id) { return projectileVector.at(id)->GetDamage(); }
	int GetOwner(int id) { return projectileVector[id]->GetOwner(); }
private:
	ProjectileManager();
	std::vector<Projectile*> projectileVector;
	Sprite* projSheet;
	int texID;
};

#endif