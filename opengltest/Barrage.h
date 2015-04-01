#include "Entity.h"


class Barrage : public Item
{
public:
	Barrage(Entity* own, float cd, float pR, float tSize,  float tduration);
	void OnHit(int projectileID);
	void OnHit(vec2 location);
	void Activate();
	void Update(float dTime);
	void OnFire();



private: 
	int size;
	float damage;
	float duration;
	bool nextShot;


};