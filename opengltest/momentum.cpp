#include "Entity.h"
#include <cmath>


void Entity::collideNonMovingWithMoving(Entity other)
{

}


void Entity::mCollideWith(Entity other)
{
	float totalXp;	//the total inital momentum on the x axis
	float totalYp;	//the total inital momentum on the y axis
	
	totalXp = momentum*cos(angle) + other.momentum*cos(other.angle);
	totalYp = momentum*sin(angle) + other.momentum*sin(other.angle);

				//totally unfinished potentially doing different smaller versions




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

