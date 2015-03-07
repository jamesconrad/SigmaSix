#include "Shield.h"

I_Shield::I_Shield(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	
}

void I_Shield::Update(float dTime)
{
	cooldown -= dTime;
}

void I_Shield::OnFire()
{

}

void I_Shield::Activate()
{
	//reset the cooldown
	cooldown = maxCooldown;

	//give the owner a 25% hp shield
	owner->giveShield();

	printf("Shielded!\n");
}

void I_Shield::OnDamage()
{
	float val = (float)rand() / RAND_MAX;

	if (val < procRate && cooldown < 0)
		Activate();
}