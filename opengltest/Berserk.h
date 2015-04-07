#pragma once
#include "Entity.h"


class Berserk :public Item
{
public: 
	Berserk(Entity* own, float cd, float pR, float dmgbuff, float rgnbuff);
	void Update(float dTime);
	void DrawAnim();
	
private:
	float DmgIncrease;
	float RegenIncrease;
	bool animDrawn;
	float duration;
	float maxDuration;

};