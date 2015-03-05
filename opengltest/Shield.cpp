#include "Shield.h"

I_Shield::I_Shield(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{

}

void I_Shield::Update(float dTime)
{
	Item::cooldown -= dTime;
}

void I_Shield::OnFire()
{

}

void I_Shield::Activate()
{

}

void I_Shield::OnDamage()
{

}