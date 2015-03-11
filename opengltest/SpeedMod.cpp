#include "SpeedMod.h"

I_SpeedMod::I_SpeedMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
}

void I_SpeedMod::Activate()
{

	//give the owner a 5% energy regen time reduction
	owner->speedMod(0.05);

	printf("Speed Increased!\n");
}
