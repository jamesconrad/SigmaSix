#ifndef PROJECTILE
#define PROJECTILE

#include "Vector2.h"
#include "Sprite.h"
#include "Dialog.h"

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
	Projectile(int managerIndex, SpriteSheetInfo sheet, float startX, float startY, float dirX, float dirY, float dmg, float maxDur, float projSpeed, int projNum, int ownerIndex);
	~Projectile();
	//Returns TRUE if the projectile needs to be removed
	bool Update(float dTime);
	int GetIndex();
	void SetIndex(int managerIndex);
	void Draw();
	float GetDamage(); 
	int GetType() { return projNum; }
	int GetOwner() { return owner; }
	vec2 GetLocation();

	RotatedRectangle GetRRect() { return rRect; }
	RECT GetRect() 
	{
		RECT tmp;
		tmp.left = x;
		tmp.right = x + w;
		tmp.bottom = y;
		tmp.top = y + h;
		return tmp;
	}
private:
	vec2 direction;
	Sprite* proj;
	float damage;
	float remainingTime;
	float speed;
	float x, y, w, h;
	float animFrame;
	int index, projNum;
	int owner;
	RotatedRectangle rRect;
	bool isBarrage;
	//RECT Rect;



};

#endif PROJECTILE