#include "Entity.h"

class I_EnergyRegen : public Item
{
public:
	I_EnergyRegen(Entity* owner, float cooldown, float procRate);
	void Activate();
private:

};