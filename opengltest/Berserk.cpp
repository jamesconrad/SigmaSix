#include "Berserk.h"


Berserk::
Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff) :Item(own, cd, pR)
{
	DmgIncrease = dmgbuff;
	RegenIncrease = rgnbuff;	
}


void Berserk::Activate()
{
	activated = true;
}


void Berserk::Update(float dtime)
{
	if (activated = true)
	{
		owner->modDamage(2);
		owner->energyRegenMod(RegenIncrease);
//		if (owner->getEnergy <= owner->getMaxEnergy)
//			owner->energy += 1;
		

	}
}
