#include "Entity.h"

class I_LifeSteal : public Item
{
public:
	I_LifeSteal(Entity* owner, float cooldown, float procRate);
	void Activate() { owner->ModHP(owner->getMaxHP() / 20); }
	void OnHit() { Activate(); }
private:

};