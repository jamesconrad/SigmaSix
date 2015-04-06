#include "Berserk.h"


Berserk::
Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff) :Item(own, cd, pR)
{
	DmgIncrease = dmgbuff;
	RegenIncrease = rgnbuff;	


	icon = new Sprite;
	aSprite = new Sprite;
	Berserk::animDrawn = false;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(38, 16);
	icon->addSpriteAnimFrame(0, 0, 0);

	aSprite->sheet = itemSheet->sheet;
	aSprite->setNumberOfAnimations(1);
	aSprite->setCurrentAnimation(0);
	aSprite->setSpriteFrameSize(37, 25);
	aSprite->addSpriteAnimRow(0, 0, 381, 26, 0, 2);

}


void Berserk::Activate()
{
	activated = true;
	cooldown = maxCooldown;

	//give the owner the shield 
	owner->GiveItem(5);
}


void Berserk::Update(float dtime)
{
	if (activated = true)
	{
		owner->modDamage(2);
		owner->energyRegenMod(RegenIncrease);
		owner->increaseNRG();


	
		
		
	}
	else
		cooldown--;


}
