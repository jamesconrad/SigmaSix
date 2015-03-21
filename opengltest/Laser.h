#include "Entity.h"

#ifndef I_Laser_H
#define I_Laser_H

class I_Laser : public Item
{


public:
	I_Laser(Entity* owner, float cooldown, float procRate, float damage, float ProjectileDuration);
	void Activate();
	void update();

private:
	void createprojectiles();
	float Damage;
	float ProjDuration;
	bool activated;

};




#endif