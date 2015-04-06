#include "Shield.h"

bool I_Shield::animDrawn = false;

I_Shield::I_Shield(Entity* owner, float cooldown, float procRate) : Item(owner, cooldown, procRate)
{
	icon = new Sprite;
	aSprite = new Sprite;
	I_Shield::animDrawn = false;
	icon->sheet = itemSheet->sheet;
	icon->setNumberOfAnimations(1);
	icon->setCurrentAnimation(0);
	icon->setSpriteFrameSize(16, 16);
	icon->addSpriteAnimFrame(0,167,109);

	aSprite->sheet = itemSheet->sheet;
	aSprite->setNumberOfAnimations(1);
	aSprite->setCurrentAnimation(0);
	aSprite->setSpriteFrameSize(50, 50);
	aSprite->addSpriteAnimRow(0, 0, 17, 51, 0, 9);
}

void I_Shield::Update(float dTime)
{
	cooldown -= dTime;
	anim += dTime;
	if (anim > 50.f)
	{
		anim = 0;
		aSprite->nextFrame();
	}

	if (owner->isShielded())
		activated = true;
	else
		activated = false;


	I_Shield::animDrawn = false;
	aSprite->setPosition(owner->getX() - 4, owner->getY());
}

void I_Shield::OnFire()
{

}

void I_Shield::Activate()
{
	//reset the cooldown
	cooldown = maxCooldown;

	//give the owner a 25% hp shield
	owner->giveShield();

	printf("Shielded!\n");
}

void I_Shield::OnDamage()
{
	float val = (float)rand() / RAND_MAX;

	if (val < procRate && cooldown < 0)
	{
		Activate();
	}
}

void I_Shield::DrawAnim()
{
	if (!I_Shield::animDrawn && activated)
	{
		aSprite->draw(0.5);
		I_Shield::animDrawn = true;
	}
}