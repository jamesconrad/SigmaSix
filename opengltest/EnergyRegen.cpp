#include "EnergyRegen.h"

I_EnergyRegen::I_EnergyRegen(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
}

void I_EnergyRegen::Activate()
{
	
	//give the owner a 5% energy regen time reduction
	owner->energyRegenMod(0.05);

	printf("Energy regen plus!\n");
}
