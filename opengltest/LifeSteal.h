#include "Item.h"

class I_LifeSteal : public Item
{
public:
	I_LifeSteal(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};