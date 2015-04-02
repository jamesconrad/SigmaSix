#include "Projectile.h"

POINT RotatePoint(float pivX, float pivY, float pX, float pY, float angle)
{
	POINT rVal;
	rVal.x = ((cos(angle) * (pX - pivX)) - (sin(angle) * (pY - pivY)) + pivX);
	rVal.y = ((sin(angle) * (pX - pivX)) + (cos(angle) * (pY - pivY)) + pivY);
	return rVal;
}

Projectile::Projectile(int managerIndex, SpriteSheetInfo sheet, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int projN, int ownerIndex)
{
	w = 9;
	h = 9;
	scale = 0.66f;//need to get these from constructor
	direction.x = dirX;
	direction.y = dirY;
	damage = dmg;
	animFrame = 0.f;
	remainingTime = maxDur;
	speed = projSpeed;
	x = startX;
	y = startY;
	index = managerIndex;
	owner = ownerIndex;
	projNum = projN;
	float deg = atan2(direction.y, direction.x) * 180 / 3.14;
	proj = new Sprite();
	proj->sheet = sheet;
	proj->setNumberOfAnimations(1);
	proj->setCurrentAnimation(0);
	proj->setPosition(x, y);
	proj->setSpriteFrameSize(w, h);
	proj->setCenter((w * scale) / 2.f, (h * scale) / 2.f);
	proj->setLayerID(1);

	if (projN == -1)
	{
		proj->setSpriteFrameSize(0, 0);
	}

	if (projN == -10)
	{
		w = 15;
		h = 15;
		proj->setSpriteFrameSize(w, h);
		proj->addSpriteAnimRow(0, 0, 21, w + 1, 0, 4);
		scale = 0.33f;
	}
	else if (projN == -11)
	{
		w = 15;
		h = 15;
		proj->setSpriteFrameSize(w, h);
		proj->addSpriteAnimRow(0, 0, 37, w + 1, 0, 4);
		scale = 0.33f;
	}
	else
		proj->addSpriteAnimRow(0, 0, 1 + projNum * (h + 1), w + 1, 0, 4);
	//scale the width and height because im lazy
	w *= scale;
	h *= scale;
}
Projectile::~Projectile()
{
	free(proj);
}

float Projectile::GetDamage()
{
	return damage;
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
	proj->draw(scale);
	/*RECT tmp = GetRect();
	glBegin(GL_QUADS);
	glVertex3f(tmp.left, tmp.bottom, 0);
	glVertex3f(tmp.right, tmp.bottom, 0);
	glVertex3f(tmp.right, tmp.top, 0);
	glVertex3f(tmp.left, tmp.top, 0);
	glEnd();*/
}



vec2 Projectile::GetLocation()
{
	vec2 loc;
	loc.x = x;
	loc.y = y;
	return loc;
}