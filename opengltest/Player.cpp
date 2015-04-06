#include "Player.h"
#include "EnergyRegen.h"

/*
Sprite* texture;
int hp, energy, energyRegen, damage;
float speed, x, y, fireRate;
vec2 direction, movement;
*/
Player::Player(ProjectileManager* projManager, SpriteSheetInfo bar, float _x, float _y)
{
	inventory.push_back(new I_EnergyRegen(this, 0, 1));
	texture = new Sprite;
	projectileManager = projManager;
	direction = vec2(0, -1);
	movement = vec2(0, 0);
	index = 0;
	hp = 100;
	maxHP = 100;
	energy = 100;
	maxEnergy = 100;
	energyRegen = 1;
	damage = 25;
	entityType = PLAYER;
	fireRate = 5;
	x = _x;
	y = _y;
	speed = 0.1;
	animFrame = 0;
	w = 34 * 0.5;
	h = 46 * 0.5;
	lastShot = 10000.f;
	energyRegenCd = 2000.f;
	lives = 3;
	for (int i = 0; i < 256; i++)
		keysPressed[i] = 0;

	shielded = false;
	aiming = false;

	texture->loadSpriteSheet("assets/playersheet_d.png");
	texture->setNumberOfAnimations(9);
	texture->setPosition(x, y);
	texture->setSpriteFrameSize(34, 46);

	texture->addSpriteAnimRow(4, 0, 1, 35.f, 0, 3);
	texture->addSpriteAnimRow(5, 0, 48, 35.f, 0, 3);
	texture->addSpriteAnimRow(6, 0, 95, 35.f, 0, 3);
	texture->addSpriteAnimRow(7, 0, 142, 35.f, 0, 3);
	texture->addSpriteAnimRow(0, 0, 189, 35.f, 0, 3);
	texture->addSpriteAnimRow(1, 0, 236, 35.f, 0, 3);
	texture->addSpriteAnimRow(2, 0, 283, 35.f, 0, 3);
	texture->addSpriteAnimRow(3, 0, 330, 35.f, 0, 3);
	//texture->addSpriteAnimRow(8, 0, 378, 35, 47, 3);
	texture->addSpriteAnimFrame(8, 0, 377);
	texture->setLayerID(1);
	texture->setCurrentAnimation(0);

	}

Player::~Player()
{

}

void Player::draw()
{
	if (!(texture->currentAnimation >= 0 && texture->currentAnimation <= 8))
		texture->setCurrentAnimation(0);
	if (aiming)
	{
		glDisable(GL_TEXTURE_2D);
		setColor(1.f, 0.f, 0.f);
		drawLine(getCX(), getCY(), getCX() + aimDir.x * 32, getCY() + aimDir.y * 32);
		glEnable(GL_TEXTURE_2D);
	}
	texture->draw(0.5f);
	for (int i = 0, s = inventory.size(); i < s; i++)
		inventory[i]->DrawAnim();
	for (int i = 0, s = inventory.size(); i < s; i++)
		inventory[i]->DrawItem(i);
}


void Player::update(float dTime)
{
	//update items
	for (int i = 0, s = inventory.size(); i < s; i++)
		inventory[i]->Update(dTime);
	//update direction and movement
	if (keysPressed['g']) this->Damage(1);
	if (keysPressed['h']) hp++;
	if (!frozen)
	{
		if (keysPressed[119])//w
		{
			y += dTime * speed;
			direction.y = 1;
			direction.x = 0;
		}
		if (keysPressed[97])//a
		{
			x -= dTime * speed;
			direction.x = -1;
			direction.y = 0;
		}
		if (keysPressed[100])//d
		{
			x += dTime * speed;
			direction.x = 1;
			direction.y = 0;
		}
		if (keysPressed[115])//s
		{
			y -= dTime * speed;
			direction.y = -1;
			direction.x = 0;
		}
		if (keysPressed[32])
		{
			if (lastShot >= 200.f && energy > 5)
			{
				shoot();
				lastShot = 0;
			}
		}
	}

	if (keysPressed[119] || keysPressed[97] || keysPressed[100] || keysPressed[115] && !frozen)
	{
		animFrame += dTime * (speed / 7.5f);
		//set curAnim based on current direction;
		if (direction.x > direction.y && direction.x > 0.f)
			curAnim = 0;
		else if (direction.x < direction.y && direction.x < 0.f)
			curAnim = 2;
		else if (direction.y > direction.x && direction.y > 0.f)
			curAnim = 3;
		else if (direction.y < direction.x && direction.y < 0.f)
			curAnim = 1;
	}
	if (Controller::instance()->Refresh())
	{
		if (sqrt(pow(Controller::instance()->leftStickX, 2) + pow(Controller::instance()->leftStickY, 2) >= 0.5) && !frozen)
		{
			direction.x = Controller::instance()->leftStickX;
			direction.y = Controller::instance()->leftStickY;
			x += direction.x * dTime * speed;
			y += direction.y * dTime * speed;
			animFrame += dTime * (speed / 7.5f);
		}
		if (Controller::instance()->IsPressed(XINPUT_GAMEPAD_A) && !gamepad_APressed && delay < -1000)
		{
			projectileManager->CreateProjectile(-1, getCX() - 2.f, getCY() - 6.f, direction.x, direction.y, 0, 100.f, 0.2f, 0);
			delay = 250;
		}
		else
			gamepad_APressed = false;
		if (sqrt(pow(Controller::instance()->rightStickX, 2) + pow(Controller::instance()->rightStickY, 2)) >= 0.75 && !frozen)
		{
			Aim(Controller::instance()->rightStickX, Controller::instance()->rightStickY);
			aiming = true;
			if (Controller::instance()->rightTrigger > 0.25f && lastShot >= 200.f && energy > 5)
			{
				shoot(Controller::instance()->rightStickX, Controller::instance()->rightStickY);
				lastShot = 0;
			}
			if (Controller::instance()->rightStickX > Controller::instance()->rightStickY && Controller::instance()->rightStickX > 0.f)
				curAnim = 0;
			else if (Controller::instance()->rightStickX < Controller::instance()->rightStickY && Controller::instance()->rightStickX < 0.f)
				curAnim = 2;
			else if (Controller::instance()->rightStickY > Controller::instance()->rightStickX && Controller::instance()->rightStickY > 0.f)
				curAnim = 3;
			else if (Controller::instance()->rightStickY < Controller::instance()->rightStickX && Controller::instance()->rightStickY < 0.f)
				curAnim = 1;
		}
		else if (Controller::instance()->rightTrigger > 0.25f && lastShot >= 200.f && energy > 5 && !frozen)
		{
			shoot();
			lastShot = 0;
		}
		else
		{
			aiming = false;
			//set curAnim based on current direction;
			if (direction.x > direction.y && direction.x > 0.f)
				curAnim = 0;
			else if (direction.x < direction.y && direction.x < 0.f)
				curAnim = 2;
			else if (direction.y > direction.x && direction.y > 0.f)
				curAnim = 3;
			else if (direction.y < direction.x && direction.y < 0.f)
				curAnim = 1;
		}
	}
	//update the shooting anim direction if gun still out
	lastShot += dTime;
	if (lastShot <= energyRegenCd || aiming)
	{
		if (curAnim < 4)
			curAnim += 4;
	}
	else if (energy < maxEnergy)
	{
		energy += energyRegen;
		if (energy > maxEnergy)
			energy = maxEnergy;
	}
	
	//DEBUG SPEED HACKS
	if (keysPressed[102])
	{
		printf("(%f, %f)\n", x, y);
		speed = 1.f;
	}
	else
		speed = 0.1f;

	if (hp <= 0)
	{
		texture->setCurrentAnimation(8);
		texture->setSpriteFrameSize(52, 30);
		deathAnim -= dTime;
		return;
	}
	else
	{
		texture->setSpriteFrameSize(34, 46);
		texture->setCurrentAnimation(curAnim);
	}
	texture->setPosition(x, y);

	if (animFrame >= 1.f)
	{
		texture->nextFrame();
		animFrame = 0.f;
	}
	
}

void Player::cancelMovement(char dir)
{
	if (dir == 'u')//up
		keysPressed[119] = false;
	else if (dir == 'l') //left *a
		keysPressed[97] = false;
	else if (dir == 'r')
		keysPressed[100] = false;
	else if (dir == 'd')
		keysPressed[115] = false;


}

void Player::handleinput(char keycode, bool press)
{
	//printf("%i - %i ", keycode, press);
	keysPressed[keycode] = press;

	if (keysPressed['e'] == true)
	{
		if (Dialog::instance()->MoreText())
			Dialog::instance()->Next();
		else
			projectileManager->CreateProjectile(-1, getCX() - 2.f, getCY() - 6.f, direction.x, direction.y, 0, 100.f, 0.2f, 0);
		keysPressed['e'] = false;
	}	
}

void Player::Aim(float normX, float normY)
{
	aimDir = vec2(normX, normY);
}

void Player::shoot()
{
	if (energy > 5)
	{
		energy -= 5;
		projectileManager->CreateProjectile(0, getCX(), getCY() + 0.5f * direction.x, direction.x, direction.y, damage, 3000.f, 0.2f, 0);
		for (int i = 0, s = inventory.size(); i < s; i++)
			inventory[i]->OnFire();
	}
}

void Player::shoot(float _x, float _y)
{
	if (_x > _y && _x > 0.f)
		curAnim = 0;
	else if (_x < _y && _x < 0.f)
		curAnim = 2;
	else if (_y > _x && _y > 0.f)
		curAnim = 3;
	else if (_y < _x && _y < 0.f)
		curAnim = 1;

	if (energy > 5)
	{
		energy -= 5;
		projectileManager->CreateProjectile(0, getCX() - 2.f, getCY() - 6.f, _x, _y, damage, 3000.f, 0.2f, 0);
		for (int i = 0, s = inventory.size(); i < s; i++)
			inventory[i]->OnFire();
	}
}

void Player::ModPos(vec2 mod)
{
	x = mod.x + x;
	y = mod.y + y;
}