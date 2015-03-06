//#include "Enemy.h"
#include "EntityManager.h"

//	--ELITES--
//		If alone refuses to run or heal
//		If with basics will attempt to back away to heal
//		Damage interupts healing and forces aggression
//		Attempts to dodge shots every few seconds when not healing
//		Stops healing if you get too close

//	--BASICS--
//		Always offensive
//		Will attempt to defend elites

Enemy::Enemy(ProjectileManager* projMan, EntityManager* entityMan, SpriteSheetInfo bar, float _x, float _y, int _i, entitytype entType)
{
	entityType = entType;
	manIndex = _i;
	projectileManager = projMan;
	entityManager = entityMan;
	texture = new Sprite;
	hpBar = new Sprite;
	hpBG = new Sprite;
	speed = 0.1f;//default 0.1f
	hp = 100;
	maxHP = 100;
	origX = x = _x;
	origX = y = _y;
	w = 34.f / 2;
	h = 46.f / 2;
	animFrame = shotTimer = 0.f;
	texture->loadSpriteSheet("assets/enemy.png");
	texture->setNumberOfAnimations(9);
	texture->setPosition(x, y);
	texture->setSpriteFrameSize(34, 46);
	texture->addSpriteAnimRow(4, 0, 1, 35.f, 0, 4);
	texture->addSpriteAnimRow(5, 0, 48, 35.f, 0, 4);
	texture->addSpriteAnimRow(6, 0, 95, 35.f, 0, 4);
	texture->addSpriteAnimRow(7, 0, 142, 35.f, 0, 4);
	texture->addSpriteAnimRow(0, 0, 189, 35.f, 0, 4);
	texture->addSpriteAnimRow(1, 0, 236, 35.f, 0, 4);
	texture->addSpriteAnimRow(2, 0, 283, 35.f, 0, 4);
	texture->addSpriteAnimRow(3, 0, 330, 35.f, 0, 4);

	texture->addSpriteAnimRow(8, 0, 189, 35.f, 47, 4);
	
	hpBG->sheet = bar;
	hpBG->setNumberOfAnimations(1);
	hpBG->setCurrentAnimation(0);
	hpBG->setSpriteFrameSize((w + 1) * 4, 10);
	hpBG->addSpriteAnimFrame(0, 0, 14);

	hpBar->sheet = bar;
	hpBar->setNumberOfAnimations(1);
	hpBar->setCurrentAnimation(0);
	hpBar->setSpriteFrameSize(w * 4, 6);
	hpBar->addSpriteAnimFrame(0, 0, 7);
	
	state = ai_state::state_chase;
}

void Enemy::update(float dTime)
{
	stateCD -= dTime;
	this->dTime = dTime;
	updateAiState();
	
	if (moving)
		animFrame += dTime * (speed / 7.5f);

	if (animFrame >= 1.f)
	{
		texture->nextFrame();
		animFrame = 0.f;
	}

	if (direction.x > direction.y && direction.x > 0.f)
		curAnim = 0;
	else if (direction.x < direction.y && direction.x < 0.f)
		curAnim = 2;
	else if (direction.y > direction.x && direction.y > 0.f)
		curAnim = 3;
	else if (direction.y < direction.x && direction.y < 0.f)
		curAnim = 1;

	if (state == state_attack)
		texture->setCurrentAnimation(curAnim + 4);
	else
		texture->setCurrentAnimation(curAnim);

	x += dTime * direction.x * speed;
	y += dTime * direction.y * speed;

	texture->setPosition(x,y);

	hpBar->setPosition(x + 0.5f, y + h + 0.5f);
	hpBG->setPosition(x, y + h);
	float hpw, hpdec = (float)hp / maxHP;
	if (hpdec <= 0)
		hpw = 0;
	else
		hpw = w * 4 * hpdec;
	hpBar->setSpriteFrameSize(hpw, 6);
	//hpBar->addSpriteAnimFrame(0, 0, 7);
	
}

void Enemy::draw()
{
	texture->draw(0.5f);
	hpBG->draw(0.25f);
	hpBar->draw(0.25f);hp--;
}

void Enemy::ModPos(vec2 mod)
{
	x += mod.x;
	y += mod.y;
}

RECT Enemy::getRect() 
{ 
	RECT tmp = { y, x, x + w, y + h };
	return tmp; 
}

void Enemy::updateAiState()
{
	switch (state)
	{
	case state_attack:
		Shoot();
		break;
	case state_passive:
		ChangeState(state_attack, 0);
		break;
	case state_patrol:

		break;
	case state_runaway:
		Runaway();
		break;
	case state_heal:
		Heal();
		break;
	case state_chase:
		//need to raycast to check if ai can hit player before changing
		Chase();
		break;
	}

}

void Enemy::Heal()
{
	float val = (float)rand() / RAND_MAX;
	if (val < 0.1)
		hp++;
	if (!Safe())
		ChangeState(state_attack, 10000);
}

void Enemy::Runaway()
{
	if (Safe())
	{
		if (entityType != ENEMY)
		{
			bcastSend('H', manIndex);
			ChangeState(state_heal, 0);
		}
	}
}

void Enemy::EvadePlayer()
{
	if (entityType != ENEMY)
		bcastSend('E', manIndex);
}

void Enemy::Patrol()
{
	ChangeState(state_chase, 0);
}

bool Enemy::Safe()
{
	return true;
}

void Enemy::Shoot()
{
	texture->setCurrentAnimation(4);
	float playerX = entityManager->getCXofID(0);
	float playerY = entityManager->getCYofID(0);

	vec2 projDir(playerX - getCX(), playerY - getCY());
	float mag = sqrt(pow(projDir.x, 2) + pow(projDir.y, 2));
	projDir.x = projDir.x / mag;
	projDir.y = projDir.y / mag;
	
	if (mag > 8 * 15)
		ChangeState(state_chase, 0);

	if (shotTimer >= 0.f)//1000.f seems to be a good speed, but 0.f is for testing
	{
		projectileManager->CreateProjectile(1, getCX(), getCY(), projDir.x, projDir.y, damage, 3000.f, 0.2f);
		shotTimer = 0.f;
	}
	else
		shotTimer += dTime;
}

void Enemy::Chase()
{
	moving = true;
	float playerX = entityManager->getCXofID(0);
	float playerY = entityManager->getCYofID(0);
	vec2 plyrDir(playerX - getCX(), playerY - getCY());
	float mag = sqrt(pow(plyrDir.x, 2) + pow(plyrDir.y, 2));

	if (mag > 10 * 15 && Safe())
	{
		ChangeState(state_patrol, 100);
		return;
	}
	else if (mag < 4 * 15)
	{
		ChangeState(state_attack, 3000);
		direction.x = 0;
		direction.y = 0;
		return;
	}

	direction.x = plyrDir.x / mag;
	direction.y = plyrDir.y / mag;
}

void Enemy::Damage(float projDamage)
{
	hp -= projDamage;
	if (hp <= 0)
	{
		bcastSend('X', manIndex);
		state = state_dead;
	}
}

void Enemy::ChangeState(ai_state newState, float cd)
{
	if (stateCD <= 0)
	{
		state = newState;
		stateCD = cd;
	}
}

void Enemy::bcastRecv(bcast broadcast)
{
	if (broadcast.msg == 'E')
		state = state_attack;
}

void Enemy::bcastSend(char msg, int sender)
{
	entityManager->bcastRecv(msg, sender);
}