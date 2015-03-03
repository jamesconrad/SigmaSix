#include "Menu.h"

MenuClass::MenuClass()
{
	background = new Sprite();
	background->loadSpriteSheet("assets/menu/background.png");
	background->setNumberOfAnimations(1);
	background->setSpriteFrameSize(1210, 833);
	background->addSpriteAnimFrame(0, 0, 0);
	background->setPosition(0, 0);
}

void MenuClass::Update(float dTime)
{

}

void MenuClass::Draw()
{
	for (int i = 0, s = effects.size(); i < s; i++)
		effects.at(i)->draw(1.f);
	background->draw(0.23f);
}

