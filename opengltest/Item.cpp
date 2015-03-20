#include "Entity.h"

Sprite* Item::itemSheet = new Sprite();

Item::Item(Entity* own, float cd, float pR)
{
	
	cooldown = cd;
	procRate = pR;
	owner = own;
	activated = false;
	anim = 0;

	if (Item::itemSheet->layerID == 0)
	{
		Item::itemSheet->loadSpriteSheet("assets/items.png");
		Item::itemSheet->setLayerID(1);
	}
}

void Item::DrawItem(int i)
{
	icon->setPosition(owner->getCX() - 134.f + (18.f * i),owner->getCY() - 108.f);
	icon->draw(0.5f);
}

void Item::DrawAnim()
{
	if (activated)
		aSprite->draw(0.5f);
}