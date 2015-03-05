#include "Tile.h"

Tile::Tile(float xPos, float yPos, float width, float height, float texX, float texY, bool solid, int texID, int texW, int texH)
{
	/*testSprite = new Sprite("images/HaggarSNEStransp.gif");
	testSprite->setNumberOfAnimations(1);
	testSprite->setSpriteFrameSize(63,99);
	testSprite->addSpriteAnimFrame(0,0,0);
	testSprite->setPosition(200,200);
	testSprite->setCenter(30,40); // center of the sprites origin for rotation
	testSprite->setLayerID(3);
		float x, y, w, h;
	bool solid;
	Sprite* mySprite;*/
	x = xPos;
	y = yPos;
	w = width;
	h = height;
	this->solid = solid;
	mySprite = new Sprite();
	mySprite->sheet.textureID = texID;
	mySprite->sheet.width = texW;
	mySprite->sheet.height = texH;
	mySprite->setNumberOfAnimations(1);
	mySprite->setPosition(xPos, yPos);
	mySprite->setSpriteFrameSize(width, height);
	mySprite->addSpriteAnimFrame(0, texX+1.f, texY);
	mySprite->setLayerID(3);
	portal = -1;
}

void Tile::Draw(float cameraPosX, float cameraPosY)
{
	mySprite->draw(1.f);
}

void Tile::MakePortal(int mapTransitionID)
{
	portal = mapTransitionID;
}

bool Tile::IsPortal()
{
	if (portal != -1)
		return true;
	else return false;
}

int Tile::GetPortalMapID()
{
	return portal;
}

int Tile::GetTexID()
{
	return mySprite->GetTexID();
}

void Tile::ForceTexID(int texID)
{
	mySprite->sheet.textureID = texID;
}

RECT Tile::GetRect()
{
	RECT tileRect;
	tileRect.left = x;
	tileRect.bottom = y;
	tileRect.top = y + h;
	tileRect.right = x + w;
	return tileRect;
}

bool Tile::GetColision()
{
	return solid;
}