#include "MaxEnergyMod.h"

I_MaxEnergyMod::I_MaxEnergyMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
}

void I_MaxEnergyMod::Activate()
{

	//give the owner a 5% Energy increase
	owner->maxEnergyMod(0.05);

	printf("Max Energy Increased!\n");
}
