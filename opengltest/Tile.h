#ifndef TILE_H
#define TILE_H
#include "Sprite.h"

class Tile
{
public:
	Tile(float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int texID, int texW, int texH);
	void Draw(float cameraPosX, float cameraPosY);
	int GetTexID();
	void ForceTexID(int texID);
	RECT GetRect();
	bool GetColision();

	/*testSprite = new Sprite("images/HaggarSNEStransp.gif");
	testSprite->setNumberOfAnimations(1);
	testSprite->setSpriteFrameSize(63,99);
	testSprite->addSpriteAnimFrame(0,0,0);
	testSprite->setPosition(200,200);
	testSprite->setCenter(30,40); // center of the sprites origin for rotation
	testSprite->setLayerID(3);*/

private:
	float x, y, w, h;
	bool solid;
	Sprite* mySprite;
};

#endif