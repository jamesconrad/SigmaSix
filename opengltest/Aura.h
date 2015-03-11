#include "Item.h"
#include "Entity.h"

class Aura : public Item
{
public:

	Aura(Entity* own, float cd, float pR);
	virtual void Activate();
	virtual void Update(float dTime);
	virtual void OnFire() { return; }
	virtual void OnDamage() { return; }

private:
	float size, scaler;//to convert health into size

};

