#include "MaxEnergyMod.h"

bool I_MaxEnergyMod::animDrawn = false;


I_MaxEnergyMod::I_MaxEnergyMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
	{
		icon = new Sprite;
		aSprite = new Sprite;
		I_MaxEnergyMod::animDrawn = false;
		icon->sheet = itemSheet->sheet;
		icon->setNumberOfAnimations(1);
		icon->setCurrentAnimation(0);
		icon->setSpriteFrameSize(16, 17);
		icon->addSpriteAnimFrame(0, 62, 388);
	}

}

void I_MaxEnergyMod::Activate()
{

	//give the owner a 5% Energy increase
	owner->maxEnergyMod(0.05);

	printf("Max Energy Increased!\n");
}
