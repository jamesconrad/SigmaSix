#include "Menu.h"
#include "EntityManager.h"
#include "Game.h"
#include "EntityManager.h"

MenuClass::MenuClass(int num)
{
	stopGame = false;
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
			if (selection == 2 || selection == 3 || selection == 4)
			{
				selection--;
			}
			else if (selection == 1)
			{
				selection = 4;
			}
			/*else if (selection == 31 || selection == 32 || selection == 33)
			{
				selection--;
			}
			else if (selection == 30)
			{
				selection = 33;
			}*/
			else if (selection == -4 || selection == -3 || selection == -2 || selection == -5)
			{
				selection++;
			}
			else if (selection == -1)
			{
				selection = -5;
			}
			/*else if (selection == -33 || selection == -31 || selection == -32)
			{
				selection--;
			}*/
			else if (selection == -30)
			{
				selection = -33;
			}
			else if (selection == -40 || selection == -50)
			{
				selection--;
			}
			else if (selection == -41 || selection == -51)
			{
				selection++;
			}
			else if (selection == 301 || selection == 302 || selection == 303)
			{
				selection = selection / 10;
			}
			else if (selection == 300)
			{
				selection = 303;
			}
			else if (selection == -301 || selection == -302 || selection == -303)
			{
				selection = selection / 10;
			}
			else if (selection == -300)
			{
				selection = -303;
			}
			else
			{
				selection = selection;
			}
		}
		if (key == 's' || key == 'S')
		{
			if (selection == 1 || selection == 2 || selection == 3)
			{
				selection++;
			}
			else if (selection == 4)
			{
				selection = 1;
			}
			/*else if (selection == 30 || selection == 32 || selection == 31)
			{
				selection++;
			}*/
			else if (selection == 33)
			{
				selection = 30;
			}
			else if (selection == -4 || selection == -3 || selection == -2 || selection == -1)
			{
			selection--;
			}
			else if (selection == -5)
			{
				selection = -1;
			}
			/*else if (selection == -30 || selection == -31 || selection == -32)
			{
			selection--;
			}*/
			else if (selection == -33)
			{
				selection = -30;
			}
			else if (selection == -40 || selection == -50)
			{
				selection--;
			}
			else if (selection == -41 || selection == -51)
			{
				selection++;
			}
			else if (selection == 301 || selection == 302 || selection == 300)
			{
				selection = selection / 10;
			}
			else if (selection == 303)
			{
				selection = 300;
			}
			else if (selection == -301 || selection == -302 || selection == -300)
			{
				selection = selection / 10;
			}
			else if (selection == -303)
			{
				selection = -300;
			}
			else
			{
				selection = selection;
			}

		}
		if (key == ' ')//commented out if not yet implemented
		{
			if (selection == 1)
			{
				startGame = true;
			}
			else if (selection == 2 || selection == 3 /*|| selection == 30 || selection == 31 || selection == 32 || selection == 33*/)
			{
				selection = selection * 10;
			}
			else if (selection == 4 || selection == -50)
			{
				exit(0);
			}
			else if (selection == -1)
			{
				startGame = true;
			}
			/*else if (selection == 30 || selection == 31 || selection == 32 || selection == 33)
			{
			selection = selection * 10;
			}
			else if (selection == 300 || selection == 310 || selection == 320 || selection == 330)
			{
				selection = selection / 10;
			}*/
			else if (selection == -2 || selection == -3 || selection == -4 || selection == -5)
			{
				selection = selection * 10;
			}
			else if (selection == -40)
			{
				stopGame = true;
				EntityManager::instance()->ModPosOfID(0, vec2(EntityManager::instance()->getXofID(0) * -1 + 120, EntityManager::instance()->getYofID(0) * -1 + 78));
			}
			else if (selection == -41 || selection == -51)
			{
				selection = selection / 10;
			}
			/*else if (selection == -30 || selection == -31 || selection == -32 || selection == -33)
			{
				selection = selection * 10;
			}
			else if (selection == -300 || selection == -310 || selection == -320 || selection == -330)
			{
				selection = selection / 10;
			}*/

			//temporary for WIP screen
			else if (selection == -20 || selection == -30 || selection == 30 || selection == 20)
			{
				selection = selection / 10;
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