#include "Entity.h"
#include <cmath>


void Entity::applyFriction()
{
	if (velocity > 0)
	{
		mFindMomentum();
		momentum  = momentum - (weight * 9.8 * CoFrictionSurface);	//because all surfaces are flat and there is no angle, 
		setVelocity();												//-the normal force is equal to the mass of the object times gravity
		if (velocity < 0)											//-the normal force is equal to the mass of the object times gravity
			velocity = 0;	// makes sure velocity never goes negative


	}
}

void Entity::setVelocity()
{

}


float Entity::relativeVelocityX(Entity other)
{
	findAngle();
	other.findAngle();

	float xVelocity = speed*cos(angle) - other.speed*cos(other.angle);

	return xVelocity;
}


float Entity::relativeVelocityY(Entity other)
{
	findAngle();
	other.findAngle();

	float yVelocity = speed*sin(angle) - other.speed*cos(other.angle);

	return yVelocity;

}

void Entity::findAngle()
{
	angle = tan(movement.y / movement.x);
}

void Entity::mFindMomentum()
{
	momentum = speed * weight;
}

