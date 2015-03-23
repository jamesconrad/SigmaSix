#include "Menu.h"
#include "EntityManager.h"

MenuClass::MenuClass(int num)
{
	startGame = false;
	selection = 1;
	background = new Sprite();
	background->setNumberOfAnimations(1);
	background->setCurrentAnimation(0);
	ChangeImage(num);
}

void MenuClass::Update(float dTime)
{

}

void MenuClass::KeyPress(unsigned char key, bool press)
{
	if (press)
	{
		if (key == 'w' || key == 'W')
		{
			if (selection <= 4 && selection > 1)
			{
				selection--;
			}
			else if (selection <= 33 && selection > 30)
			{
				selection--;
			}
			else if (selection >= -5 && selection < -1)
			{
				selection++;
			}
			else if (selection <= -33 && selection > -30)
			{
				selection++;
			}
			else if (selection = -41)
			{
				selection++;
			}
			else if (selection = -51)
			{
				selection++;
			}
		}
		if (key == 's' || key == 'S')
		{
			if (selection < 4 && selection >= 1)
			{
				selection++;
			}
			else if (selection < 33 && selection >= 30)
			{
				selection++;
			}
			else if (selection > -5 && selection <= -1)
			{
			selection--;
			}
			else if (selection > -33 && selection <= -30)
			{
			selection--;
			}
			else if (selection = -40)
			{
			selection--;
			}
			else if (selection = -50)
			{
			selection--;
			}
		}
		if (key == ' ')
		{
			if (selection == 1)
			{
				startGame = true;
			}
			else if (selection == 2)
			{
				selection *= 10;
			}
			else if (selection == 3)
			{
				selection *= 10;
			}
			else if (selection == 4)
			{
				exit(0);
			}
			else if (selection == 20)
			{
				selection /= 10;
			}
			else if (selection == 30)
			{
				selection *= 10;
			}
			else if (selection == 31)
			{
				selection *= 10;
			}
			else if (selection == 32)
			{
				selection *= 10;
			}
			else if (selection == 33)
			{
				selection *= 10;
			}
			else if (selection == 300)
			{
				selection /= 10;
			}
			else if (selection == 310)
			{
				selection /= 10;
			}
			else if (selection == 320)
			{
				selection /= 10;
			}
			else if (selection == 330)
			{
				selection /= 10;
			}
			else if (selection == -1)
			{
				selection = 1;
				startGame = true;
			}
			else if (selection == -2)
			{
				selection *= 10;
			}
			else if (selection == -20)
			{
				selection /= 10;
			}
			else if (selection == -3)
			{
				selection *= 10;
			}
			else if (selection == -300 || selection == -310 || selection == -320 || selection == -330)
			{
				selection /= 10;
			}
			else if (selection == -4)
			{
				selection *= 10;
			}
			else if (selection == -40)
			{
				selection = 1;
			}
			else if (selection == -41)
			{
				selection /= 10;
			}
			else if (selection == -5)
			{
				selection *= 10;
			}
			else if (selection == -51)
			{
				selection /= 10;
			}
			else if (selection == -50)
			{
				exit(0);
			}
		}
		ChangeImage(selection);
	}

}
void MenuClass::Draw()
{
	for (int i = 0, s = effects.size(); i < s; i++)
		effects.at(i)->draw(1.f);
	background->draw(0.25f);
}

void MenuClass::ChangeImage(int num)
{
	std::string filepath;
	filepath.append("assets/menu/menu_");
	char menunum[8];
	_itoa_s(num, menunum, 10);
	filepath.append(menunum);
	filepath.append(".png");
	background->loadSpriteSheet(filepath.c_str());
	background->addSpriteAnimFrame(0, 0, 0);
	if (num < 0)
	{
		background->setSpriteFrameSize(1024, 768);
		background->setPosition(EntityManager::instance()->getXofID(0) - 120, EntityManager::instance()->getYofID(0) - 60);
	}
	else if (num > 0)
	{
		background->setSpriteFrameSize(1210, 833);
		background->setPosition(0, 0);
	}
}