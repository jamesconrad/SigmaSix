#include "Entity.h"


class Barrage : public Item
{
public:
	Barrage(float tSize, float tdamage, float tduration, Entity* own, float cd, float pR);
	void OnHit();
	void Activate();



private: 
	int size;
	float damage;
	float duration;


};