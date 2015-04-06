#include "Entity.h"
#include "Shield.h"
#include "Aura.h"
#include "Berserk.h"
#include "DamageMod.h"
#include "EnergyRegen.h"
#include "LifeSteal.h"
#include "MaxEnergyMod.h"
#include "MaxHealthMod.h"
#include "SpeedMod.h"
#include "Laser.h"
#include "Barrage.h"

void Entity::GiveItem(int itemId)
{
	switch (itemId)
	{
	case 0:
		inventory.push_back(new I_SpeedMod(this, 0, 1));
		break;
	case 1:
		inventory.push_back(new I_DamageMod(this, 0, 1));
		break;
	case 2:
		inventory.push_back(new I_EnergyRegen(this, 0, 1));
		break;
	case 3:
		inventory.push_back(new I_MaxEnergyMod(this, 0, 1));
		break;

	case 4:
		inventory.push_back(new I_MaxHealthMod(this, 0, 1));
		break;
	case 5:
		inventory.push_back(new Berserk(this, 0, 12, 3, 3));
		break;
	case 6:
		inventory.push_back(new Barrage(this, 0, 1, 2, 1));
		break;

	case 10:
		inventory.push_back(new I_Shield(this, 10, 0.1));
		break;
	case 11:
		inventory.push_back(new I_LifeSteal(this, 0, 1));
		break;

	default:
		inventory.push_back(new I_Shield(this, 10, 0.1));
		printf("ERROR: Invalid Item ID: %i", itemId);
		break;
	}
}

void Entity::OnHit(vec2 location)
{
	for (int i = 0, s = inventory.size(); i < s; i++)
	{
		
			inventory[i]->OnHit(location);
	
	}


}

void Entity::setlowHP()
{
	if (hp <= maxHP*.2)
	hp = maxHP *.2;
}

void Entity::OnHit()
{
	for (int i = 0, s = inventory.size(); i < s; i++)
	{

		inventory[i]->OnHit();

	}


}
void Entity::increaseNRG()
{
	energy = energy + 1;

}