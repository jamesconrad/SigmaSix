#include "Sprite.h"

class Object
{
public:
	Object(float xPos, float yPos, bool solid);
	/*
	testSprite = new Sprite("images/HaggarSNEStransp.gif");
	testSprite->setNumberOfAnimations(1);
	testSprite->setSpriteFrameSize(63,99);
	testSprite->addSpriteAnimFrame(0,0,0);
	testSprite->setPosition(200,200);
	testSprite->setCenter(30,40); // center of the sprites origin for rotation
	testSprite->setLayerID(3);
	*/

private:
	float x, y, w, h;
	bool solid;
	Sprite* mySprite;
};