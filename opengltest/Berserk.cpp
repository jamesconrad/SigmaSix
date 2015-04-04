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
	{
		icon = new Sprite;
		aSprite = new Sprite;
		icon->sheet = itemSheet->sheet;
		icon->setNumberOfAnimations(1);
		icon->setCurrentAnimation(0);
		icon->setSpriteFrameSize(22, 16);
		icon->addSpriteAnimFrame(0, 38, 388);
	}
}


void Berserk::Update(float dtime)
{
	if (activated = true)
	{
		owner->modDamage(2);
		owner->energyRegenMod(RegenIncrease);
		owner->increaseNRG();

	}
}
