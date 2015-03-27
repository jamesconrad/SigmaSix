#include "Dialog.h"

#define PORT_W 32
#define PORT_H 32

Dialog::Dialog()
{
	dialogbox = new Sprite();
	dialogbox->loadSpriteSheet("assets/dia.png");
	dialogbox->setSpriteFrameSize(1024, 173);
	dialogbox->setNumberOfAnimations(1);
	dialogbox->addSpriteAnimFrame(0, 0, 0);
	dialogbox->setCurrentAnimation(0);

	Sprite* port = new Sprite();
	std::string fp;
	char buff[16];
	for (int i = 0; i < 11; i++)
	{
		fp = "assets/portraits/";
		_ltoa_s(i, buff, 10);
		fp.append(buff);
		fp.append(".png");
		port->loadSpriteSheet(fp.c_str());
		port->setSpriteFrameSize(PORT_W, PORT_H);
		port->setNumberOfAnimations(1);
		port->addSpriteAnimFrame(i, (i % PORT_W) * PORT_W, (i / PORT_W) * PORT_W);
		port->setCurrentAnimation(0);

		portraits.push_back(port);
	}
}

void Dialog::Say(entitytype ent, int diaNum)
{
	std::string fp;
	std::string buffer;
	std::string search;
	char buff[16];

	//prep filepath
	fp = "assets/dialog/";
	_ltoa_s(ent, buff, 10);
	fp.append(buff);
	fp.append(".txt");

	//prep search string
	search = ":";
	_ltoa_s(diaNum, buff, 10);
	search.append(buff);
	search.append(":\n");

	std::ifstream file(fp, std::ios::in);
	
	while (strcmp(buffer.c_str(), search.c_str()))
	{

	}
}