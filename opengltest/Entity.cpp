#include "Entity.h"
#include "Shield.h"

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