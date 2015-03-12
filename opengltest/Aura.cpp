#include "Aura.h"


Aura::Aura(Entity* own, float cd, float pR) :Item(own, cd, pR)
{
	scaler = 2;
	size = (own->getHP())*scaler;
	damage = owner->getDamage();
	return;
}

//STILL WORKING ON THIS
void Aura::createProjectiles()
{
	float locX = owner->getX();
	float locY = owner->getY();

	for (int i = size; i >= -size; i--)
	{//this way it puts a projectile in every space within the duration 
		ProjectileManager::instance()->CreateProjectile(66, (locX - i), (locY - i), 0, 0, damage, duration, 0);
	}
		// start x & start Y are the bottom left hand corner 
		// max dur = aprox 1 
		//projetile speed = 0 
		//dir x & y = 0
		
}

void Aura::Update(float dTime)
{

	size = (owner->getMaxHP() - owner->getHP())*scaler;
	cooldown -= dTime;
	createProjectiles();
}

void Aura::Activate()
{
	
}

