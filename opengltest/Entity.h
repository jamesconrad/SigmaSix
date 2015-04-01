#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Sprite.h"
#include "ProjectileManager.h"

struct bcast
{
	char msg;
	int sender;
};

#ifndef ENTTYPE_S
#define ENTTYPE_S
enum entitytype {
	PLAYER = 0,
	ENEMY = 10,
	ELITE = 11,
	NEUTRAL1 = -1,
	NEUTRAL2 = -2,
	NEUTRAL3 = -3,
	BOSS = 100,
	MINIBOSS1 = 1,
	MINIBOSS2 = 2,
	MINIBOSS3 = 3,
	MINIBOSS4 = 4,
	MINIBOSS5 = 5,
	MINIBOSS6 = 6
};
#endif
class Item;

class Entity
{
public:

	// Bonnie's shit Useless, do not touch just for math report
	void mCollideWith(Entity other);
	void mFindMomentum();
	void applyFriction();
	void findAngle();
	float relativeVelocityX(Entity other);
	float relativeVelocityY(Entity other);
	void collideNonMovingWithMoving(Entity other);


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
			tmp.bottom = getCY() - 8;
			tmp.right = getCX() + 5;
			tmp.top = getCY() + 5;
		}
		return tmp;
	};
	entitytype GetType() { return entityType; }
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
	virtual void maxHealthMod(float value) { return; }
	virtual void lifeSteal(float value) { return; }
	virtual void maxEnergyMod(float value) { return; }

	virtual void bcastRecv(bcast broadcast) {}
	virtual void bcastSend(char msg, int sender) {}

	bool isShielded() { return shielded; }//
	void GiveItem(int itemId);//
	int GetLives() { return lives; }//
	void ModLives(int mod) { lives += mod; deathAnim = 2000.f; }//
	void ModHP(int mod) { hp += mod; }//

	int GetCollidingID(){ return 1; }
	vec2 GetDirection(){ return direction; }
	float GetLocationX(){ return x; }
	float getLocationY(){ return y; }
	vec2 BarrageLocation(int ID){ return projectileManager->GetLocation(ID); }

	void increaseNRG();

	bool IsDeathAnimOver() { return (deathAnim <= 0); }

	float delay;
	bool gamepad_APressed = false;
protected:
	entitytype entityType;
	std::vector<Item*> inventory;
	Sprite* texture, *hpBar, *energyBar, *hpBG, *energyBG;
	ProjectileManager* projectileManager;
	float x, y, w, h;
	vec2 direction, movement;
	bool moving;
	float origX, origY;
	float speed, fireRate;
	int index;
	int  energy, energyRegen, damage;
	int  hp, maxHP, maxEnergy;	
	float animFrame, dTime;
	int curAnim;
	float shotTimer;
	int manIndex;
	bool frozen; 
	float lastShot, energyRegenCd;
	bool keysPressed[256];
	int lives;
	float deathAnim = 2000.f;

	//again, this is bonnie's 
	float momentum, weight, angle;

	//ITEM VARS
	bool shielded;
	float toggleLifeSteal;
};


class Item
{
public:
	Item(Entity* own, float cd, float pR);
	virtual void Activate() { return; }
	virtual void Update(float dTime) { return; }
	virtual void OnFire() { return; }
	virtual void OnHit() { return; }
	virtual void OnDamage() { return; }
	virtual void DrawItem(int i);
	virtual void DrawAnim();
	
	static Sprite* itemSheet;
protected:
	float cooldown, procRate, maxCooldown, anim;
	bool activated;
	Sprite* icon;
	Sprite* aSprite;
	Entity* owner;
};

#endif