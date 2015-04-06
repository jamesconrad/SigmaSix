#include "Berserk.h"


Berserk::
Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff) :Item(own, cd, pR)
{
	DmgIncrease = dmgbuff;
	RegenIncrease = rgnbuff;	
	duration = 0;
	maxDuration = 2000.f;
	maxCooldown = 0;
	activated = false;


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
	aSprite->addSpriteAnimRow(0, -38, 131, 38, 0, 2);

}


void Berserk::Activate()
{


	
}


void Berserk::Update(float dtime)
{
	if (owner->getHP() <= owner->getMaxHP()*.2 && cooldown <= 0)
	{
		activated = true;
	}

	if (duration > maxDuration)
	{
		activated = false;
		duration = 0;
		cooldown = maxCooldown;
	}

	

	if (activated = true)
	{
		owner->setlowHP();
		owner->modDamage(2);
		owner->increaseNRG();	
		duration += dtime;
		Berserk::animDrawn = false;
		aSprite->setPosition(owner->getX() , owner->getY()+ 15);

		anim += dtime;
		if (anim > 100.f)
		{
			anim = 0;
			aSprite->nextFrame();
		}
	}
	else
		cooldown -= dtime;



}


void Berserk::DrawAnim()
{
	if (!Berserk::animDrawn && activated)
	{
		aSprite->draw(0.5);
		Berserk::animDrawn = true;
	}
}
