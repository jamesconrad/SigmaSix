#include "Menu.h"

MenuClass::MenuClass(int num)
{
	background = new Sprite();
	background->setNumberOfAnimations(1);
	ChangeImage(num);
}

void MenuClass::Update(float dTime)
{

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
	itoa(num, menunum, 10);
	filepath.append(menunum);
	filepath.append(".png");
	background->loadSpriteSheet(filepath.c_str());
	background->setSpriteFrameSize(1210, 833);
	background->setPosition(0, 0);
	background->addSpriteAnimFrame(0, 0, 0);
}