#include "Projectile.h"

POINT RotatePoint(float pivX, float pivY, float pX, float pY, float angle)
{
	POINT rVal;
	rVal.x = ((cos(angle) * (pX - pivX)) - (sin(angle) * (pY - pivY)) + pivX);
	rVal.y = ((sin(angle) * (pX - pivX)) + (cos(angle) * (pY - pivY)) + pivY);
	return rVal;
}

Projectile::Projectile(int managerIndex, int texID, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int projN)
{
	w = 9;
	h = 9;
	float scale = 0.5f;//need to get these from constructor
	direction.x = dirX;
	direction.y = dirY;
	damage = dmg;
	animFrame = 0.f;
	remainingTime = maxDur;
	speed = projSpeed;
	x = startX;
	y = startY;
	index = managerIndex;
	projNum = projN;
	float deg = atan2(direction.y, direction.x) * 180 / 3.14; // wtf is atan2?
	//POINT r1 = RotatePoint(x + (w * scale / 2.f), y + (h * scale / 2.f), startX, startY, deg);
	//POINT r2 = RotatePoint(x + (w * scale / 2.f), y + (h * scale / 2.f), startX + w * scale, startY + h * scale, deg);
	//r1.x >= r2.x ? rRect.maxX = r1.x, rRect.minX = r2.x : rRect.maxX = r2.x, rRect.minX = r1.x;
	//r1.y >= r2.y ? rRect.maxY = r1.y, rRect.minY = r2.y : rRect.maxY = r2.y, rRect.minY = r1.y;
	/*
	float s = sin(deg), c = cos(deg);
	rRect.minX -= startX;
	rRect.minY -= startY;
	rRect.maxX += w*scale - startX;
	rRect.maxY += h*scale - startY;
	float maxXnew = rRect.maxX * c - rRect.maxY * s;
	float maxYnew = rRect.maxX * s + rRect.maxY * c;
	float minXnew = rRect.minX * c - rRect.minY * s;
	float minYnew = rRect.minX * s + rRect.minY * s;
	rRect.maxX = maxXnew + startX;
	rRect.maxY = maxYnew + startY;
	rRect.minX = minXnew + startX;
	rRect.minY = minYnew + startY;
	*/
	proj = new Sprite();
	proj->sheet.textureID = texID;
	proj->sheet.width = 60;
	proj->sheet.height = 20;
	proj->setNumberOfAnimations(1);
	proj->setCurrentAnimation(0);
	proj->setPosition(x, y);
	proj->setSpriteFrameSize(w, h);
	proj->setCenter((w * scale) / 2.f, (h * scale) / 2.f);
	proj->addSpriteAnimRow(0, 0, 1 + projNum * (h + 1), w + 1, 0, 4);
	proj->setLayerID(1);
	//proj->setOrientation(atan2(direction.y, direction.x) * 180 / 3.14);
	//texture->addSpriteAnimRow(animnum,startx,starty,spacingx,spacingy,numframe)

	//scale the width and height because im lazy
	w *= 0.5f;
	h *= 0.5f;
	/*	*/
}
Projectile::~Projectile()
{
	free(proj);
}

bool Projectile::Update(float dTime)
{
	x += dTime * direction.x * speed;
	y += dTime * direction.y * speed;
	//rRect.maxX += dTime * direction.x * speed;
	//rRect.maxY += dTime * direction.y * speed;
	//rRect.minX += dTime * direction.x * speed;
	//rRect.minY += dTime * direction.y * speed;
	
	proj->setPosition(x, y);

	remainingTime -= dTime;

	animFrame += dTime * (speed / 10);

	if (animFrame >= 1.f)
	{
		proj->nextFrame();
		animFrame = 0.f;
	}
	

	if (remainingTime < 0.f)
		return true;
	return false;
}

int Projectile::GetIndex()
{
	return index;
}

void Projectile::SetIndex(int managerIndex)
{
	index = managerIndex;
}

void Projectile::Draw()
{
	proj->draw(0.66);
}