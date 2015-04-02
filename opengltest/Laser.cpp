#include "Laser.h"




I_Laser::
I_Laser(Entity* owner, float cooldown, float procRate, float damage, float ProjectileDuration) : Item(owner, cooldown, procRate)
{
	Damage = damage;
	ProjDuration = ProjectileDuration;
}


void I_Laser::
Activate()
{
	icon = new Sprite;
	aSprite = new Sprite;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(16, 16);
	icon->addSpriteAnimFrame(0, 95, 388);


}

void I_Laser::
update()
{
	if (owner->getHP() < owner->getMaxHP() / 4)
	{
		activated = true; 
	}


}


void I_Laser::
createprojectiles()
{
	float locX = owner->getX();
	float locY = owner->getY();

	for (int i = -1; i > 1; i = i + .1)
	{
		for (int j = -1; j > 1; j = j + 1)			//I am assuming that you use the relation between dirX and dirY to determine the direction, 
		{
			ProjectileManager::instance()->CreateProjectile(66, (locX), (locY), i, j, Damage, ProjDuration, 0, owner->GetIndex());	//I wanted it to shoot in all directions so I gave it quiet a few combinations

		}
	}
}