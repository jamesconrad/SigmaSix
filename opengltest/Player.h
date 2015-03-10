#ifndef PLAYER_H
#define PLAYER_H

#include "ProjectileManager.h"
#include "Entity.h"
#include "Shield.h"

class Player : public Entity
{
public:
	Player(ProjectileManager* projManager, SpriteSheetInfo bar, float x, float y);
	~Player();
	void draw();
	void update(float dTime);
	void handleinput(char keycode, bool press);
	float getX() { return x; }
	float getY() { return y; }
	float getCX() { return x + w * 0.5f; }
	float getCY() { return y + h * 0.5f; }
	float getHP() { return hp; }
	float getEnergy() { return energy; }
	float getMaxHP() { return maxHP; }
	float getMaxEnergy() { return maxEnergy; }
	void giveShield() { shielded = true; }
	virtual void cancelMovement(char dir);
	void Damage(float projDamage) 
	{ 
		if (!shielded)
		{
			for (int i = 0, s = inventory.size(); i < s; i++)
				inventory[i]->OnDamage();
			if (hp < projDamage)
				hp = 0;
			else
				hp -= projDamage;
		}
		else
			shielded = false;
	}
	RECT getRect() { RECT tmp = { x, y + h, x + w, y }; return tmp; }
	void ModPos(vec2 mod);
	void shoot();
private:
	std::vector<Item*> inventory;
	Sprite* texture, *hpBar, *energyBar, *hpBG, *energyBG;
	ProjectileManager* projectileManager;
	int hp, energy, energyRegen, damage, maxHP, maxEnergy;
	float speed, x, y, w, h, fireRate;
	vec2 direction, movement;
	float animFrame, lastShot;
	bool keysPressed[256];
	int curAnim;
	bool shielded;
};

#endif