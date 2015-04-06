#include "Lifesteal.h"

I_LifeSteal::I_LifeSteal(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	icon = new Sprite;
	aSprite = new Sprite;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(16, 15);
	icon->addSpriteAnimFrame(0, 114, 108);
}