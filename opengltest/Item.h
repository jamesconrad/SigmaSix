#ifndef ITEM
#define ITEM

#include "Entity.h"

class Item
{
public:
	Item(Entity* own, float cd, float pR) { cooldown = cd; procRate = pR; owner = own; }
	virtual void Activate() { return; }
	virtual void Update(float dTime) { return; }
	virtual void OnFire() { return; }
	virtual void OnDamage() { return; }
protected:
	float cooldown, procRate;
	Entity* owner;
};

#endif ITEM