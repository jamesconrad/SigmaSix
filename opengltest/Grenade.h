#include "Entity.h"



class Grenade :public Item
{
public:
	Grenade(Entity* own, float cd, float pR, float damage);
	void Activate();
	void Update(float dTime);
	 void OnHit(vec2 location);
	void DrawItem(int i);
	void DrawAnim();
	static Sprite* itemSheet;
	void checks();


protected:
	float cooldown, procRate, maxCooldown, anim;
	bool activated;
	Sprite* icon;
	Sprite* aSprite;
	Entity* owner;
	bool animDrawn;
	float duration;
	float maxDuration;

	float damage;
	bool ready;




};