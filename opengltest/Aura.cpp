#include "Aura.h"


Aura::Aura(Entity* own, float cd, float pR) :Item(own, cd, pR)
{
	scaler = 2;
	size = (own->getHP)*scaler;
	return;
}

void Aura::Update(float dTime)
{


}