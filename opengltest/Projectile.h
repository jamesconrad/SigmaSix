#ifndef PROJECTILE
#define PROJECTILE

#include "Vector2.h"
#include "Sprite.h"

#ifndef RRECT
#define RRECT
struct RotatedRectangle
{
	float maxX, minX, maxY, minY;
};
#endif RRECT

class Projectile
{
public:
	Projectile(int managerIndex, int texID, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int projNum);
	~Projectile();
	//Returns TRUE if the projectile needs to be removed
	bool Update(float dTime);
	int GetIndex();
	void SetIndex(int managerIndex);
	void Draw();
	float GetDamage() { return damage; }
	int GetType() { return projNum; }

	RotatedRectangle GetRRect() { return rRect; }
	RECT GetRect() { return RECT{ y, x, x + w, y + h }; }
private:
	vec2 direction;
	Sprite* proj;
	float damage;
	float remainingTime;
	float speed;
	float x, y, w, h;
	float animFrame;
	int index, projNum;
	RotatedRectangle rRect;
	//RECT Rect;
};

#endif PROJECTILE