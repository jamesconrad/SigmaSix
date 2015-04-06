#include "Aura.h"


Aura::Aura(Entity* own, float cd, float pR) :Item(own, cd, pR)
{
	scaler = 2;
	size = (own->getHP())*scaler;
	damage = owner->getDamage();

	icon = new Sprite;
	aSprite = new Sprite;
	Aura::animDraw = false;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(38, 16);
	icon->addSpriteAnimFrame(0, 0, 0);

	aSprite->sheet = itemSheet->sheet;
	aSprite->setNumberOfAnimations(1);
	aSprite->setCurrentAnimation(0);
	aSprite->setSpriteFrameSize(50, 50);
	aSprite->addSpriteAnimRow(0, 0, 17, 51, 0, 9);
	
}

void Aura::DrawAnim()
{

}

//STILL WORKING ON THIS
void Aura::createProjectiles()
{
	float locX = owner->getX();
	float locY = owner->getY();

	for (int i = size; i >= -size; i--)
	{//this way it puts a projectile in every space within the duration 
		for (int j = size; j >= -size; j--)
		{
			ProjectileManager::instance()->CreateProjectile(66, (locX - i), (locY - j), 0, 0, damage, ProjDuration, 0, owner->GetIndex());
		}
	}	// start x & start Y are the bottom left hand corner 
		// max dur = aprox 1 
		//projetile speed = 0 
		//dir x & y = 0
		
}

void Aura::Update()
{
	if (activated == true)
	{
		while (tElapsed < AbilityDuration)
		{
			Update();
			tElapsed--;

			size = (owner->getMaxHP() - owner->getHP())*scaler;

			createProjectiles();
		}
	}
	else
		cooldown--;

}

void Aura::Activate()
{
	cooldown = maxCooldown;
	{
		icon = new Sprite;
		aSprite = new Sprite;
		icon->sheet = itemSheet->sheet;
		icon->setNumberOfAnimations(1);
		icon->setCurrentAnimation(0);
		icon->setSpriteFrameSize(16, 16);
		icon->addSpriteAnimFrame(0, 20, 108); 
	}
}

