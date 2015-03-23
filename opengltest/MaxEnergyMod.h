#include "Entity.h"

class I_MaxEnergyMod : public Item
{
public:
	I_MaxEnergyMod(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};