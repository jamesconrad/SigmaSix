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

Enemy::Enemy(ProjectileManager* projMan, EntityManager* entityMan, SpriteSheetInfo bar, float _x, float _y, int _i, entitytype entType, int _index)
{
	//GENERAL VARS
	stateBool = false;
	cooldown = 0;
	entityType = entType;
	manIndex = _i;
	projectileManager = projMan;
	entityManager = entityMan;
	texture = new Sprite;
	hpBar = new Sprite;
	hpBG = new Sprite;
	speed = 0.1f;//default 0.1f
	origX = x = _x;
	origX = y = _y;
	shielded = false;
	index = _index;
	curAnim = 0;
	animFrame = shotTimer = 0.f;
	texture->setNumberOfAnimations(9);
	texture->setPosition(x, y);

	if (entityType == ENEMY)
	{
		w = 34;
		h = 46;
		hp = 100;
		maxHP = 100;
		damage = 10;
		texture->loadSpriteSheet("assets/enemy.png");
		texture->setSpriteFrameSize(w, h);
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 4);
		texture->addSpriteAnimRow(5, 0, 48, w + 1, 0, 4);
		texture->addSpriteAnimRow(6, 0, 95, w + 1, 0, 4);
		texture->addSpriteAnimRow(7, 0, 142, w + 1, 0, 4);
		texture->addSpriteAnimRow(0, 0, 189, w + 1, 0, 4);
		texture->addSpriteAnimRow(1, 0, 236, w + 1, 0, 4);
		texture->addSpriteAnimRow(2, 0, 283, w + 1, 0, 4);
		texture->addSpriteAnimRow(3, 0, 330, w + 1, 0, 4);

		texture->addSpriteAnimRow(8, 0, 189, w + 1, 47, 4);
	}
	else if (entityType == ELITE)
	{
		w = 34;
		h = 46;
		hp = 200;
		maxHP = 200;
		damage = 20;
		texture->loadSpriteSheet("assets/elite.png");
		texture->setSpriteFrameSize(w, h);
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 4);
		texture->addSpriteAnimRow(5, 0, 48, w + 1, 0, 4);
		texture->addSpriteAnimRow(6, 0, 95, w + 1, 0, 4);
		texture->addSpriteAnimRow(7, 0, 142, w + 1, 0, 4);
		texture->addSpriteAnimRow(0, 0, 189, w + 1, 0, 4);
		texture->addSpriteAnimRow(1, 0, 236, w + 1, 0, 4);
		texture->addSpriteAnimRow(2, 0, 283, w + 1, 0, 4);
		texture->addSpriteAnimRow(3, 0, 330, w + 1, 0, 4);

		texture->addSpriteAnimRow(8, 0, 189, w + 1, 47, 4);
	}
	else if (entityType == NEUTRAL1)
	{
		w = 34;
		h = 46;
		hp = 200;
		maxHP = 200;
		damage = 20;
		speed /= 2;
		texture->loadSpriteSheet("assets/npc1.png");
		texture->setSpriteFrameSize(w, h);
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 4);
		texture->addSpriteAnimRow(5, 0, 48, w + 1, 0, 4);
		texture->addSpriteAnimRow(6, 0, 95, w + 1, 0, 4);
		texture->addSpriteAnimRow(7, 0, 142, w + 1, 0, 4);
		texture->addSpriteAnimRow(0, 0, 189, w + 1, 0, 4);
		texture->addSpriteAnimRow(1, 0, 236, w + 1, 0, 4);
		texture->addSpriteAnimRow(2, 0, 283, w + 1, 0, 4);
		texture->addSpriteAnimRow(3, 0, 330, w + 1, 0, 4);

		texture->addSpriteAnimRow(8, 0, 189, w + 1, 47, 4);
	}
	else if (entityType == NEUTRAL2)
	{
		w = 34;
		h = 46;
		hp = 200;
		maxHP = 200;
		damage = 20;
		speed /= 2;
		texture->loadSpriteSheet("assets/npc2.png");
		texture->setSpriteFrameSize(w, h);
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 4);
		texture->addSpriteAnimRow(5, 0, 48, w + 1, 0, 4);
		texture->addSpriteAnimRow(6, 0, 95, w + 1, 0, 4);
		texture->addSpriteAnimRow(7, 0, 142, w + 1, 0, 4);
		texture->addSpriteAnimRow(0, 0, 189, w + 1, 0, 4);
		texture->addSpriteAnimRow(1, 0, 236, w + 1, 0, 4);
		texture->addSpriteAnimRow(2, 0, 283, w + 1, 0, 4);
		texture->addSpriteAnimRow(3, 0, 330, w + 1, 0, 4);

		texture->addSpriteAnimRow(8, 0, 189, w + 1, 47, 4);
	}
	else if (entityType == NEUTRAL3)
	{
		w = 34;
		h = 46;
		hp = 200;
		maxHP = 200;
		damage = 20;
		speed /= 2;
		texture->loadSpriteSheet("assets/npc3.png");
		texture->setSpriteFrameSize(w, h);
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 4);
		texture->addSpriteAnimRow(5, 0, 48, w + 1, 0, 4);
		texture->addSpriteAnimRow(6, 0, 95, w + 1, 0, 4);
		texture->addSpriteAnimRow(7, 0, 142, w + 1, 0, 4);
		texture->addSpriteAnimRow(0, 0, 189, w + 1, 0, 4);
		texture->addSpriteAnimRow(1, 0, 236, w + 1, 0, 4);
		texture->addSpriteAnimRow(2, 0, 283, w + 1, 0, 4);
		texture->addSpriteAnimRow(3, 0, 330, w + 1, 0, 4);

		texture->addSpriteAnimRow(8, 0, 189, w + 1, 47, 4);
	}
	else if (entityType == BOSS)
	{
		w = 42;
		h = 88;
		hp = 500;
		maxHP = 500;
		damage = 50;
		texture->loadSpriteSheet("assets/boss.png");
		texture->setSpriteFrameSize(w, h);
		//pewpewing
		texture->addSpriteAnimRow(4, 0, 1, w + 1, 0, 7);
		texture->addSpriteAnimRow(5, 0, h+2, w + 1, 0, 7);
		texture->addSpriteAnimRow(6, 0, 2*h+3, w + 1, 0, 7);
		texture->addSpriteAnimRow(7, 0, 3*h+4, w + 1, 0, 7);
		//walking
		texture->addSpriteAnimRow(0, 0, 4*h+5, w + 1, 0, 7);
		texture->addSpriteAnimRow(1, 0, 5*h+6, w + 1, 0, 7);
		texture->addSpriteAnimRow(2, 0, 6*h+7, w + 1, 0, 7);
		texture->addSpriteAnimRow(3, 0, 7*h+8, w + 1, 0, 7);
	}
	else
	{
		hp = 350;
		maxHP = 350;
		damage = 30;
		w = 69;
		h = 75;
		std::string filePath;
		char buff[16];
		filePath = "assets/miniboss";
		_ltoa_s(entityType, buff, 10);
		filePath.append(buff);
		filePath.append(".png");
		texture->loadSpriteSheet(filePath.c_str());
		texture->setSpriteFrameSize(w, h);
		//pewpewing
		texture->addSpriteAnimRow(7, 0, 1, w + 1, 0, 7);
		texture->addSpriteAnimRow(5, 0, h + 2, w + 1, 0, 7);
		texture->addSpriteAnimRow(6, 0, 2 * h + 3, w + 1, 0, 7);
		texture->addSpriteAnimRow(4, 0, 3 * h + 4, w + 1, 0, 7);
		//walking
		texture->addSpriteAnimRow(3, 0, 4 * h + 5, w + 1, 0, 7);
		texture->addSpriteAnimRow(1, 0, 5 * h + 6, w + 1, 0, 7);
		texture->addSpriteAnimRow(2, 0, 6 * h + 7, w + 1, 0, 7);
		texture->addSpriteAnimRow(0, 0, 7 * h + 8, w + 1, 0, 7);
	}
	texture->setCurrentAnimation(0);

	
	state = ai_state::state_chase;
	w /= 2;
	h /= 2;	
	
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
}

void Enemy::update(float dTime)
{
	if (hp <= 0.f)
	{
		EntityManager::instance()->DeleteEntity(index);
		return;
	}

	stateCD -= dTime;
	this->dTime = dTime;
	updateAiState();
	
	if (moving || entityType == BOSS)
	{
		if (state == state_patrol)
		{
			animFrame += dTime * (speed / 15.f);
		}
		else
			animFrame += dTime * (speed / 7.5f);
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

	if (animFrame >= 1.f)
	{
		texture->nextFrame();
		animFrame = 0.f;
	}


	if (state == state_patrol && moving)
	{
		x += dTime * direction.x * (speed / 2.f);
		y += dTime * direction.y * (speed / 2.f);
	}
	else if (moving)
	{
		x += dTime * direction.x * speed;
		y += dTime * direction.y * speed;
	}

	texture->setPosition(x,y);

	hpBar->setPosition(x + 0.5f, y + h + 0.5f);
	hpBG->setPosition(x, y + h);
	float hpw, hpdec = (float)hp / maxHP;
	if (hpdec <= 0)
		hpw = 0;
	else
		hpw = w * 4 * hpdec;
	hpBar->setSpriteFrameSize(hpw, 6);
	
}

void Enemy::draw()
{
	texture->draw(0.5f);
	hpBG->draw(0.25f);
	hpBar->draw(0.25f);
}

void Enemy::ModPos(vec2 mod)
{
	x += mod.x;
	y += mod.y;
}

RECT Enemy::getRect() 
{ 
	RECT tmp;
	tmp.right = x;
	tmp.left = x + w;
	tmp.bottom = y;
	tmp.top = y + h;
	return tmp; 
}

void Enemy::updateAiState()
{
	if (entityType == NEUTRAL1 || entityType == NEUTRAL2 || entityType == NEUTRAL3)
	{
		if (hp < maxHP)
		{
			Runaway();
		}
		else
			Patrol();
		return;
	}
	switch (state)
	{
	case state_attack:
		Shoot();
		break;
	case state_passive:
		if (hp < maxHP)
			ChangeState(state_patrol, 100);
		break;
	case state_patrol:
		Patrol();
		break;
	case state_runaway:
		Runaway();
		break;
	case state_heal:
		Heal();
		break;
	case state_chase:
		Chase();
		break;
	}

}

void Enemy::Heal()
{
	moving = false;
	direction = vec2(0, 0);
	float val = (float)rand() / RAND_MAX;
	if (val < 0.25 && hp <= 100)
		hp++;
	if (!Safe())
		ChangeState(state_attack, 10000);
	if (hp / maxHP >= 0.75)
		ChangeState(state_chase, 0);
}

void Enemy::Runaway()
{
	moving = true;
	if (Safe())
	{
		if (entityType != ENEMY)
		{
			bcastSend('H', manIndex);
			ChangeState(state_heal, 0);
		}
	}
	float playerX = entityManager->getCXofID(0);
	float playerY = entityManager->getCYofID(0);
	vec2 plyrDir(playerX - getCX(), playerY - getCY());
	float mag = sqrt(pow(plyrDir.x, 2) + pow(plyrDir.y, 2));

	direction.x = -plyrDir.x/mag;
	direction.y = -plyrDir.y/mag;
	
}

void Enemy::Patrol()
{
	moving = true;
	cooldown -= dTime;
	//move to random point
	if (!stateBool)
	{
		//pick a new direction
		if ( cooldown <= 0)
		{
			direction.x = (float(rand()) / float(RAND_MAX)) * (1 - (-1)) + (-1);
			direction.y = (float(rand()) / float(RAND_MAX)) * (1 - (-1)) + (-1);
			cooldown = 1000.f;
			stateBool = true;
		}
	}
	else
	{
		if (cooldown <= 0)
		{
			direction.x = -direction.x;
			direction.y = -direction.y;
			cooldown = 1000.f;
			stateBool = false;
		}
	}

	if (!Safe() && (entityType !=  NEUTRAL1 && entityType != NEUTRAL2 && entityType != NEUTRAL3))
		ChangeState(state_chase, 0);
}

bool Enemy::Safe()
{
	float playerX = entityManager->getCXofID(0);
	float playerY = entityManager->getCYofID(0);
	vec2 plyrDir(playerX - getCX(), playerY - getCY());
	float mag = sqrt(pow(plyrDir.x, 2) + pow(plyrDir.y, 2));

	if (mag > 8 * 15)
	{
		return true;
	}
	else
		return false;
}

void Enemy::Shoot()
{
	moving = false;
	texture->setCurrentAnimation(4);
	float playerX = entityManager->getCXofID(0);
	float playerY = entityManager->getCYofID(0);

	vec2 projDir(playerX - getCX(), playerY - getCY());
	float mag = sqrt(pow(projDir.x, 2) + pow(projDir.y, 2));
	projDir.x = projDir.x / mag;
	projDir.y = projDir.y / mag;

	direction = projDir;
	
	if (mag > 8 * 15)
		ChangeState(state_chase, 0);

	if (shotTimer >= 1000.f)//1000.f seems to be a good speed, but 0.f is for testing
	{
		projectileManager->CreateProjectile(1, getCX(), getCY(), projDir.x, projDir.y, damage, 3000.f, 0.2f, GetIndex());
		shotTimer = 0.f;
	}
	else
		shotTimer += dTime;

	if (hp / maxHP <= 0.25 && entityType != ENEMY)
		ChangeState(state_runaway, 0);
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
	if (!shielded)
	{
		hp -= projDamage;
		if (hp <= 0)
		{
			bcastSend('X', manIndex);
			state = state_dead;
		}
	}
	else
		shielded = false;
}

void Enemy::ChangeState(ai_state newState, float cd)
{
	if (stateCD <= 0)
	{
		state = newState;
		stateCD = cd;
		stateBool = false;
		cooldown = 0;
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