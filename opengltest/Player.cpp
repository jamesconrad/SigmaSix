#include "Player.h"

/*
Sprite* texture;
int hp, energy, energyRegen, damage;
float speed, x, y, fireRate;
vec2 direction, movement;
*/
Player::Player(ProjectileManager* projManager, SpriteSheetInfo bar, float _x, float _y)
{
	texture = new Sprite;
	projectileManager = projManager;
	direction = vec2(0, -1);
	movement = vec2(0, 0);
	hp = 100;
	maxHP = 100;
	energy = 100;
	maxEnergy = 100;
	energyRegen = 1;
	damage = 5;
	fireRate = 5;
	x = _x;
	y = _y;
	speed = 0.1;
	animFrame = 0;
	w = 34 * 0.5;
	h = 46 * 0.5;
	lastShot = 10000.f;
	for (int i = 0; i < 256; i++)
		keysPressed[i] = 0;

	inventory.push_back(new I_Shield(this, 0.1f, 0.1f));

	texture->loadSpriteSheet("assets/playersheet_d.png");
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
	//texture->addSpriteAnimRow(animnum,startx,starty,spacingx,spacingy,numframe)
	texture->setLayerID(1);

	//texture->addSpriteAnimRow(1, 0, 40, 31, 0, 4);
	/*
	mySprite->setNumberOfAnimations(1);
	mySprite->setPosition(xPos, yPos);
	mySprite->setSpriteFrameSize(width, height);
	mySprite->addSpriteAnimFrame(0, texX+1.f, texY);
	*/
}

Player::~Player()
{

}

void Player::draw()
{
	texture->draw(0.5f);
	//printf("%f, %f\n", x, y);
	/*RECT tmp = getRect();
	glBegin(GL_QUADS);
	glVertex3f(tmp.left, tmp.bottom, 0);
	glVertex3f(tmp.right, tmp.bottom, 0);
	glVertex3f(tmp.right, tmp.top, 0);
	glVertex3f(tmp.left, tmp.top, 0);
	glEnd();*/

}

void Player::update(float dTime)
{
	//update items
	for (int i = 0, s = inventory.size(); i < s; i++)
		inventory[i]->Update(dTime);
	//update direction and movement
	if (keysPressed['g']) this->Damage(1);
	if (keysPressed['h']) hp++;
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
		if (lastShot >= 150.f && energy > 10)
		{
			shoot();
			lastShot = 0;
		}
	}
	
	//set curAnim based on current direction;
	if (direction.x > direction.y && direction.x > 0.f)
		curAnim = 0;
	else if (direction.x < direction.y && direction.x < 0.f)
		curAnim = 2;
	else if (direction.y > direction.x && direction.y > 0.f)
		curAnim = 3;
	else if (direction.y < direction.x && direction.y < 0.f)
		curAnim = 1;

	//update the shooting anim direction if gun still out
	lastShot += dTime;
	if (lastShot <= 2000.f)
	{
		if (curAnim <= 4)
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

	texture->setPosition(x, y);
	texture->setCurrentAnimation(curAnim);

	if (keysPressed[119] || keysPressed[97] || keysPressed[100] || keysPressed[115])
		animFrame += dTime * (speed / 7.5f);

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
	printf("%i - %i ", keycode, press);
	keysPressed[keycode] = press;
}

void Player::shoot()
{
	if (energy > 10)
	{
		energy -= 10;
		projectileManager->CreateProjectile(0, getCX(), getCY() + 0.5f * direction.x, direction.x, direction.y, damage, 3000.f, 0.2f);
		for (int i = 0, s = inventory.size(); i < s; i++)
			inventory[i]->OnFire();
	}
}

void Player::ModPos(vec2 mod)
{
	x = mod.x + x;
	y = mod.y + y;
}