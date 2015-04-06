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
		if (!animDrawn && activated)
		{
			aSprite->draw(0.5);
			animDrawn = true;
		}
		return;
	}
	void checks();


protected:

	static bool animDrawn;
	float duration;
	float damage;
	bool ready;




};