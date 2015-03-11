#include "EnergyRegen.h"

I_EnergyRegen::I_EnergyRegen(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{

}

void I_EnergyRegen::Update()
{
	cooldown -= dTime;
}

void I_EnergyRegen::OnFire()
{

}

void I_EnergyRegen::Activate()
{
	
	//give the owner a 25% hp shield
	owner->giveShield();

	printf("Shielded!\n");
}

void I_EnergyRegen::OnDamage()
{
	float val = (float)rand() / RAND_MAX;

	if (val < procRate && cooldown < 0)
		Activate();
}