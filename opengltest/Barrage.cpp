#include "Barrage.h"



Barrage::Barrage(Entity* own, float cd, float pR, float tSize,  float tduration) : Item(owner, cooldown, procRate)
{
	size = tSize;
	damage = own->getDamage();
	duration = tduration;
}




void Barrage:: 
Update(float dTime)
{
	cooldown -= dTime;

	if (cooldown <= 0)
	{
		nextShot = true;
	}

}

void Barrage::
Activate()
{
	icon = new Sprite;
	aSprite = new Sprite;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(16, 16);
	icon->addSpriteAnimFrame(0, 20, 388);
	//PUT STUFF HERE
}




void Barrage::
OnHit(int projectileID)
{
	if (nextShot = true)
	{
		//the location of impact
		float x = 0;
		float y = 0; //BONNYMAN YOU NEED TO DERIVE THESE
		owner->BarrageLocation(projectileID);

		for (int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				ProjectileManager::instance()->CreateProjectile(69, x + i, y + j, 0, 0, damage, duration, 0, owner->GetIndex());
			}
		}
	}
}
 

void Barrage::
OnHit(vec2 location)
{
	if (nextShot = true)
	{
	
		for (int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				ProjectileManager::instance()->CreateProjectile(69, location.x + i, location.y + j, 0, 0, damage, duration, 0, owner->GetIndex());
			}
		}
	}

}



void Barrage::
OnFire()
{/*
	if (nextShot = true)
	{
		nextShot = false;
		cooldown = maxCooldown;
		float dirX = owner->GetDirection().x;
		float dirY = owner->GetDirection().y;
		ProjectileManager::instance()->CreateProjectile(66, (owner->GetLocationX), (owner->getLocationY), dirX, dirY, damage, duration, 0, owner->GetIndex());

	}
	*/
}














