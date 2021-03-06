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
	void MakePortal(int mapTransitionID);
	bool IsPortal();
	int GetPortalMapID();
	virtual void update(float dTime) {}

	/*testSprite = new Sprite("images/HaggarSNEStransp.gif");
	testSprite->setNumberOfAnimations(1);
	testSprite->setSpriteFrameSize(63,99);
	testSprite->addSpriteAnimFrame(0,0,0);
	testSprite->setPosition(200,200);
	testSprite->setCenter(30,40); // center of the sprites origin for rotation
	testSprite->setLayerID(3);*/

protected:
	float x, y, w, h;
	bool solid;
	int portal;
	Sprite* mySprite;
};

class AnimTile : public Tile
{
public:
	void update(float dTime)
	{
		lastFrame += dTime;
		if (lastFrame >= animDelay)
			mySprite->nextFrame();
	}
	AnimTile(float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int texID, int texW, int texH, int texSpacing, int numFrames, float animDelay) :
		Tile(xPos, yPos, width, height, texX, texY, solid, texID, texW, texH)
	{
		mySprite->addSpriteAnimRow(0, texX, texY, texSpacing, 0, numFrames);
		lastFrame = 0;
	}

private:
	int animFrame;
	float lastFrame, animDelay;
};

#endif