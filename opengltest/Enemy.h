#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

enum ai_state
{
	state_attack = 0,
	state_passive = 1,
	state_patrol = 2,
	state_runaway = 3,
	state_heal = 4,
	state_chase = 5,
	state_defend = 6,
	state_ability_1 = 11,
	state_ability_2 = 12,
	state_ability_3 = 13,
	state_ability_4 = 14,
	state_ability_5 = 15,
	state_ability_6 = 16,
};
class ProjectileManager;
class EntityManager;
class Enemy : public Entity
{
public:
	Enemy(ProjectileManager* projMan, EntityManager* entityMan, SpriteSheetInfo bar);
	virtual void draw();
	virtual void update(float dTime); // will need to do ai stuff
	virtual void ModPos(vec2 mod);
	virtual float getCX() { return x + w * 0.25f; }
	virtual float getCY() { return y + h * 0.25f; }
	virtual RECT getRect();
	virtual void Damage(float projDamage);
	void updateAiState();
	void EvadePlayer();
	bool Safe();
	void Shoot();
	void Chase();

private:
	Sprite* texture, *hpBar, *energyBar, *hpBG, *energyBG;
	EntityManager* entityManager;
	ProjectileManager* projectileManager;
	int  energy, energyRegen, damage;
	float speed, x, y, w, h, fireRate;
	int  hp, maxHP;
	vec2 direction, movement;
	float animFrame, dTime;
	int curAnim;
	ai_state state;
	bool moving;
	float shotTimer;
};

#endif