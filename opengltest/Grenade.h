#include "Entity.h"



class Grenade :public Item
{
public:
	Grenade(Entity* own, float cd, float pR, float damage);
	void Activate() { return; }
	void Update(float dTime);
	void OnHit(vec2 location);
	void DrawItem(int i) { return; }
	void DrawAnim(){
		if (!Grenade::animDrawn && activated)
		{
			aSprite->draw(0.5);
			Grenade::animDrawn = true;
		}
		return;
	}
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