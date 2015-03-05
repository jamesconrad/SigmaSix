#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Sprite.h"

class Entity
{
public:
	virtual void draw() {}; //default does nothing needs to be overriden by owner
	virtual void update(float dTime) {}; //^
	virtual void handleinput(char keycode, bool press) {}; //^
	virtual float getX() { return 0.f; }
	virtual float getY() { return 0.f; }
	virtual RECT getRect() { RECT tmp = { 0, 0, 0, 0 }; return tmp; }
	virtual void ModPos(vec2) {};
	virtual void Damage(float damage){};
	virtual float getCX() { return 0.f; }
	virtual float getCY() { return 0.f; }
	virtual float getHP() { return 0.f; }
	virtual float getEnergy() { return 0.f; }
	virtual float getMaxHP() { return 0.f; }
	virtual float getMaxEnergy() { return 0.f; }

	virtual void modDamage(float change) { return; }
	virtual float getDamage() { return 0.0f; }
	virtual void giveShield(float shield) { return; }


private:
	
};
#endif