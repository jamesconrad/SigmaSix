#include "Berserk.h"


Berserk::
Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff) :Item(own, cd, pR)
{
	DmgIncrease = dmgbuff;
	RegenIncrease = rgnbuff;	
	duration = 0;
	maxDuration = 20;


	icon = new Sprite;
	aSprite = new Sprite;
	Berserk::animDrawn = false;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(22, 19);
	icon->addSpriteAnimFrame(0, 38, 107);

	aSprite->sheet = itemSheet->sheet;
	aSprite->setNumberOfAnimations(1);
	aSprite->setCurrentAnimation(0);
	aSprite->setSpriteFrameSize(37, 25);
	aSprite->addSpriteAnimRow(0, 0, 131, 38, 0, 2);

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
	cooldown -= dtime;
	if (duration < maxDuration)
	{
		activated = false;
		duration = 0;
		cooldown = maxCooldown;
	}


	if (activated = true)
	{
		owner->modDamage(2);
		owner->energyRegenMod(RegenIncrease);
		owner->increaseNRG();	
		duration++;
		Berserk::animDrawn = false;
		aSprite->setPosition(owner->getX() , owner->getY()+ 15);
	}
	else
		cooldown--;



}


void Berserk::DrawAnim()
{
	if (!Berserk::animDrawn && activated)
	{
		aSprite->draw(0.5);
		Berserk::animDrawn = true;
	}
}
