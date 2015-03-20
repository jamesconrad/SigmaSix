#include "Entity.h"
#include "ProjectileManager.h"

class Aura : public Item
{
public:

	Aura(Entity* own, float cd, float pR);
	virtual void Activate();
	virtual void Update();
	virtual void OnFire() { return; }
	virtual void OnDamage() { return; }
	double distanceToPlayer();
	void createProjectiles();

private:
	float size;		// the radius away from the player this will impact 
	float scaler;//to convert health into size
	float damage;
	float AbilityDuration;
	float ProjDuration;
	float tElapsed;

};

