#pragma once
#include "Entity.h"



class Grenade :public Item
{
public:
	Grenade(Entity* own, float cd, float pR, float damage);
	void Activate() override;
	void Update(float dTime);
	void OnHit(vec2 location);
	void DrawAnim(){
		if (!animDrawn && activated)
		{
			aSprite->draw(0.5);
			animDrawn = true;
		}
		return;
	}
	

private:

	static bool animDrawn;
	float duration;
	float damage;
	bool ready;




};