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
	ProjectileManager();
	void CreateProjectile(int projNum, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed);
	void RemoveProjectile(int index);
	void Update(float dTime);
	void Draw();
	std::vector<Projectile*>* GetProjectileVector() { return &projectileVector; }
	float DamageOfID(int id) { return projectileVector.at(id)->GetDamage(); }
private:
	std::vector<Projectile*> projectileVector;
	Sprite* projSheet;
	int texID;
};

#endif