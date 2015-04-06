#include "Grenade.h"


Grenade::Grenade(Entity* own, float cd, float pR, float tdamage) : Item(own, cd, pR)
{
	damage = tdamage;
	ready = true;
	
	

	icon = new Sprite;
	aSprite = new Sprite;
	Grenade::animDrawn = false;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(15, 17);
	icon->addSpriteAnimFrame(0, 80, 107);

	aSprite->sheet = itemSheet->sheet;
	aSprite->setNumberOfAnimations(11);
	aSprite->setCurrentAnimation(0);
	aSprite->setSpriteFrameSize(32, 30);
	aSprite->addSpriteAnimRow(0, -32, 158, 33, 0, 11);
	


}


void Grenade::OnHit(vec2 location)
{
	if ( ready)
	{
		for (int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				ProjectileManager::instance()->CreateProjectile(69, location.x + i, location.y + j, 0, 0, damage, duration, 0, owner->GetIndex());
				aSprite->setPosition(location.x, location.y);
				ready = false;
			}
		}
	}
}


void Grenade::Update(float dTime)
{
	cooldown--;
	if (cooldown <= 0)
		ready = true;


	checks();
}

void Grenade::checks()
{
	if (cooldown < 0)
		cooldown = 0;
	
}




void Grenade::DrawAnim()
{
	if (!Grenade::animDrawn && activated)
	{
		aSprite->draw(0.5);
		Grenade::animDrawn = true;
	}
}
