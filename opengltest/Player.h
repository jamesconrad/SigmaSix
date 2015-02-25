#ifndef PLAYER_H
#define PLAYER_H

#include "ProjectileManager.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player(ProjectileManager* projManager, SpriteSheetInfo bar);
	~Player();
	virtual void draw();
	virtual void update(float dTime);
	virtual void handleinput(char keycode, bool press);
	virtual float getX() { return x; }
	virtual float getY() { return y; }
	virtual float getCX() { return x + w * 0.5f; }
	virtual float getCY() { return y + h * 0.5f; }
	virtual float getHP() { return hp; }
	virtual float getEnergy() { return energy; }
	virtual float getMaxHP() { return maxHP; }
	virtual float getMaxEnergy() { return maxEnergy; }
	virtual void Damage(float projDamage) 
	{ 
		if (hp < projDamage)
			hp = 0;
		else
			hp -= projDamage;
	}
	virtual RECT getRect() { RECT tmp = { x, y + h, x + w, y }; return tmp; }
	virtual void ModPos(vec2 mod);
	void shoot();
private:
	Sprite* texture, *hpBar, *energyBar, *hpBG, *energyBG;
	ProjectileManager* projectileManager;
	int hp, energy, energyRegen, damage, maxHP, maxEnergy;
	float speed, x, y, w, h, fireRate;
	vec2 direction, movement;
	float animFrame, lastShot;
	bool keysPressed[256];
	int curAnim;
};

#endif