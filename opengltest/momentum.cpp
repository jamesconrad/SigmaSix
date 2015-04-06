#include "Entity.h"
#include <cmath>


void Entity::applyFriction()
{
	if (velocity > 0)
	{
		velocity  = velocity - (weight * 9.8 * CoFrictionSurface);
	}


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

