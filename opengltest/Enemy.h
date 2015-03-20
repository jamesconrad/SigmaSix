#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

enum ai_state
{
	state_dead = -1,
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
	Enemy(ProjectileManager* projMan, EntityManager* entityMan, SpriteSheetInfo bar, float x, float y, int index, entitytype entType, int managerIndex);
	void draw();
	void update(float dTime); // will need to do ai stuff
	void ModPos(vec2 mod);
	int GetIndex() { return index; }
	float getCX() { return x + w * 0.25f; }
	float getCY() { return y + h * 0.25f; }
	float getX() { return x; }
	float getY() { return y; }
	void Freeze(bool status) { frozen = status; }
	float getSpeed() { return speed; }
	void giveShield() { shielded = true; }
	entitytype GetType() { return entityType; }
	RECT getRect();
	void Damage(float projDamage);
	void updateAiState();
	bool Safe();
	void Shoot();
	void Chase();
	void Patrol();
	void Runaway();
	void Heal();

	void ChangeState(ai_state newState, float cd);

	void bcastRecv(bcast broadcast);
	void bcastSend(char msg, int sender);

private:
	EntityManager* entityManager;
	ai_state state;
	entitytype entityType;
	float stateCD, cooldown;
	bool stateBool;
};

#endif