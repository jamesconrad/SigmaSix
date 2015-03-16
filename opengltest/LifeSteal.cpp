#include "LifeSteal.h"

I_LifeSteal::I_LifeSteal(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
}

void I_LifeSteal::Activate()
{

	//give the owner a X% speed increase
	owner->lifeSteal(0.05);
	
	printf("Gained Lifesteal!\n");
}
