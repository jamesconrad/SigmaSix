#include "MaxHealthMod.h"

I_MaxHealthMod::I_MaxHealthMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
}

void I_MaxHealthMod::Activate()
{

	//give the owner a 5% Health increase
	owner->maxHealthMod(0.05);

	printf("Max Health Increased!\n");
}
