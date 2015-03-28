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

void Entity::GiveItem(int itemId)
{
	switch (itemId)
	{
	case 0:
		inventory.push_back(new I_Shield(this, 10, 0.1));
		break;
	case 1:
		break;
	}
}


void Entity::increaseNRG()
{
	energy = energy + 1;

}