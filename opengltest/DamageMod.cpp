#include "DamageMod.h"

I_DamageMod::I_DamageMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
	draw = false;
}

void I_DamageMod::Activate()
{

	//give the owner a 5% damage increase
	owner->damageMod(0.05);

	printf("Damage Increased!\n");
}
