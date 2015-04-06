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