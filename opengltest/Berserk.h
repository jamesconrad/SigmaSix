#include "Entity.h"


class Berserk :public Item
{
public: 
	Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff);
	void Activate();
	void Update(float dTime);
	
private:
	float DmgIncrease;
	float RegenIncrease;


};