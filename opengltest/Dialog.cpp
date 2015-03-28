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

	dT = linenum = 0;
	

	head = new speech;
	head->next = NULL;
	iter = head;
}

void Dialog::Say(entitytype ent, int diaNum)
{
	ResetSay();
	std::string fp;
	std::string buffer = "";
	std::string search;
	char buff[128];

	//prep filepath
	fp = ReturnFP(ent);
	iter->speaker = ent;
	//prep search string
	search = ReturnSearch(diaNum);

	std::ifstream file(fp, std::ios::in);
	
	if (!file.is_open())
		printf("ERROR: Invalid Entity to start talking");

	int nextSpeaker;

	bool done = false;

	do
	{

		do
		{
			getline(file, buffer);
		} while (strcmp(buffer.c_str(), search.c_str()) != 0);
		std::string tmp = search.substr(1, search.size() - 1).c_str();
		//iter->speaker = _atoi64(search.substr(1, search.size() - 1).c_str());

		search = ";";
		while (iter->text.size() == 0 || strcmp(iter->text[iter->text.size() - 1].c_str(), search.c_str()) != 0)
		{
			file.getline(buff, 64, '\n');
			iter->text.push_back(std::string(buff));
		}
		if (iter->text[iter->text.size() - 2].find("[") != std::string::npos)
		{
			int first = iter->text[iter->text.size() - 2].find('[');
			int last = iter->text[iter->text.size() - 2].find('>');
			buffer = iter->text[iter->text.size() - 2].substr(first + 1, last - first - 1);

			file.close();
			nextSpeaker = _atoi64(buffer.c_str());
			fp = ReturnFP(nextSpeaker).c_str();
			file.open(fp.c_str(), std::ios::in);

			first = iter->text[iter->text.size() - 2].find("]");
			buffer = iter->text[iter->text.size() - 2].substr(last + 1, first - last - 1);
			search = ReturnSearch(_atoi64(buffer.c_str()));

			iter->text.pop_back();
		}
		else
			done = true;
		
		iter->text.pop_back();
		iter->text.shrink_to_fit();
		
		if (!done)
		{
			iter->next = new speech;
			iter->next->speaker = nextSpeaker;
			iter = iter->next;
			iter->next = NULL;
		}

	} while (done == false);

	moreText = true;

	return;
}

std::string Dialog::ReturnFP(int fileNum)
{
	char buff[8];
	//prep filepath
	std::string fp  = "assets/dialog/";
	_ltoa_s(fileNum, buff, 10);
	fp.append(buff);
	fp.append(".txt");

	return fp;
}

std::string Dialog::ReturnSearch(int diaNum)
{
	char buff[8];
	//prep search string
	std::string search = ":";
	_ltoa_s(diaNum, buff, 10);
	search.append(buff);
	search.append(":");
	return search;
}

void Dialog::Next()
{
	dT = 0;
	linenum = 0;
	if (waiting)
	{
		linenum = iter->text.size() - 1;
		dT = 1000000;
	}
	else
	{
		if (iter->next != NULL)
		{
			iter = iter->next;
			waiting = true;
		}
		else
		{
			moreText = false;
		}
	}
}

void DeleteList(speech** head)
{
	speech* current = *head;
	speech* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void Dialog::ResetSay()
{
	DeleteList(&head);
	head = new speech;
	head->next = NULL;
	iter = head;
}

void drawText(std::string s, float posX, float posY, int numChars)
{
	glPushMatrix();
	glRasterPos2f(posX, posY);
	const char *text = s.c_str();
	for (int i = 0; i<numChars; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glPopMatrix();
}

void Dialog::Update(float dTime, float pX, float pY)
{
	dT += dTime;
	if (iter->speaker == 0)
	{
		dialogbox->setPosition(pX - 128, pY - 98);
		portraits[0]->setPosition(pX - 128, pY - 98);

		top = false;
		pd = 0;
	}
	else
	{
		dialogbox->setPosition(pX - 128, pY + 98);
		switch (iter->speaker)
		{
		case -1: pd = 1; break;
		case 1: pd = 2; break;
		}
		portraits[pd]->setPosition(pX - 128, pY - 98);

		top = true;
	}

	numChars = dT / 500;
	if (numChars >= iter->text[linenum].length() && linenum < iter->text.size() - 1)
	{
		linenum++;
		dT = 0;
	}
	else if (linenum == iter->text.size())
	{
		waiting = false;
	}
	for (int i = 0; i < linenum; i++)
	{
		top ? tY = pY + 98 - 8 * i : tY = pY - 58 - 8 * i;
		drawText(iter->text[i], pX - 96, tY, iter->text[i].size());
	}
	top ? tY = pY + 98 - 8 * linenum : tY = pY - 58 - 8 * linenum;
	drawText(iter->text[linenum], pX - 96, tY, numChars);
}

void Dialog::Draw()
{
	for (int i = 0; i < linenum; i++)
	{
		top ? tY = pY + 98 - 8 * i : tY = pY - 58 - 8 * i;
		drawText(iter->text[i], pX - 96, tY, iter->text[i].size());
	}
	top ? tY = pY + 98 - 8 * linenum : tY = pY - 58 - 8 * linenum;
	drawText(iter->text[linenum], pX - 96, tY, numChars);
}

