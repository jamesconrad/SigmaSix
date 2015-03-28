#include "Entity.h"

class I_LifeSteal : public Item
{
public:
	I_LifeSteal(Entity* owner, float cooldown, float procRate);
	void Activate() { /*increase hp */}
	void OnHit() { Activate(); }
private:

};