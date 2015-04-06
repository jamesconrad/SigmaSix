#include "MaxHealthMod.h"

I_MaxHealthMod::I_MaxHealthMod(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	Activate();
	{
		icon = new Sprite;
		aSprite = new Sprite;
		icon->sheet = itemSheet->sheet;
		icon->setNumberOfAnimations(1);
		icon->setCurrentAnimation(0);
		icon->setSpriteFrameSize(16, 17);
		icon->addSpriteAnimFrame(0, 147, 107);
	}
}

void I_MaxHealthMod::Activate()
{

	//give the owner a 5% Health increase
	owner->maxHealthMod(0.05);

	printf("Max Health Increased!\n");
}
