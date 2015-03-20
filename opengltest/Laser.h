#include "Entity.h"

#ifndef I_Laser_H
#define I_Laser_H

class I_Laser : public Item
{


public:
	I_Laser(Entity* owner, float cooldown, float procRate, float damage);
	void Activate();
	void Update(float dTime);

private:
	float Damage;

};




#endif