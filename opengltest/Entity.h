#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Sprite.h"

#ifndef BCAST_S
#define BCAST_S
struct bcast
{
	char msg;
	int sender;
};
#endif BCAST_S

class Entity
{
public:
	virtual void draw() {}; //default does nothing needs to be overriden by owner
	virtual void update(float dTime) {}; //^
	virtual void handleinput(char keycode, bool press) {}; //^
	virtual float getX() { return 0.f; }
	virtual float getY() { return 0.f; }
	RECT getRect() 
	{
		RECT tmp;
		if (index != 0)
		{
			tmp.left = x;
			tmp.right = x + w;
			tmp.top = y + h;
			tmp.bottom = y;
		}
		else
		{
			tmp.left = getCX() - 5;
			tmp.bottom = getCY() - 7;
			tmp.right = getCX() + 5;
			tmp.top = getCY() + 5;
		}
		return tmp;
	};
	void UpdateIndex(int i) { index = i; }
	virtual void ModPos(vec2) {};
	virtual void Damage(float damage){};
	virtual float getCX() { return 0.f; }
	virtual float getCY() { return 0.f; }
	virtual float getHP() { return 0.f; }
	virtual float getEnergy() { return 0.f; }
	virtual float getMaxHP() { return 0.f; }
	virtual float getMaxEnergy() { return 0.f; }
	virtual float getSpeed() { return 0.f; }
	virtual void Freeze(bool status) { return; }
	virtual void OnHit() { return; }
	virtual int GetIndex() { return 0; }

	virtual void modDamage(float change) { return; }
	virtual float getDamage() { return 0.0f; }
	virtual void giveShield() { return; }
	virtual void energyRegenMod(float value) { return; }
	virtual void speedMod(float value) { return; }
	virtual void damageMod(float value) { return; }

	virtual void bcastRecv(bcast broadcast) {}
	virtual void bcastSend(char msg, int sender) {}


protected:
	float x, y, w, h;
	int index;
	
};
#endif