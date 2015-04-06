#include "SpeedMod.h"

I_SpeedMod::I_SpeedMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
	draw = false;
}

void I_SpeedMod::Activate()
{

	//give the owner a 5% speed increase
	owner->speedMod(0.05);

	printf("Speed Increased!\n");
}
