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

	Sprite* sheet = new Sprite();
	sheet->loadSpriteSheet("assets/portraits.png");

	Sprite* port;
	for (int i = 0; i < 20; i++)
	{
		port = new Sprite();
		port->sheet = sheet->sheet;
		port->setSpriteFrameSize(PORT_W, PORT_H);
		port->setNumberOfAnimations(1);
		port->addSpriteAnimFrame(0, (i % 5) * PORT_W, (i / 5) * PORT_W);
		port->setCurrentAnimation(0);

		portraits.push_back(port);
	}

	dT = linenum = pd = 0;
	moreText = false;
	waiting = false;
	

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

	try
	{
		if (!file.is_open())
			throw 1;
	}
	catch (int e)
	{
		printf("ERROR: Entity has no txt file");
		return;
	}

	int nextSpeaker;

	bool done = false;

	do
	{
		if (!file.is_open())
		{
			printf("ERROR: Dialogue has failed to open a file");
			break;
		}
		do
		{
			getline(file, buffer);
		} while (strcmp(buffer.c_str(), search.c_str()) != 0);
		std::string tmp = search.substr(1, search.size() - 1).c_str();
		//iter->speaker = _atoi64(search.substr(1, search.size() - 1).c_str());

		search = ";";
		while (iter->text.size() == 0 || strcmp(iter->text[iter->text.size() - 1].c_str(), search.c_str()) != 0)
		{
			file.getline(buff, 128, '\n');
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
			//char err[512];
			//printf(strerror_s(1,err,1));

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

	} while (done == false && !file.eof());

	iter = head;

	moreText = true;
	waiting = true;

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
	if (waiting)
	{
		waiting = false;
		linenum = iter->text.size() - 1;
		dT = 1000000;
	}
	else
	{
		if (iter->next != NULL)
		{
			iter = iter->next;
			waiting = true;
			dT = 0;
			linenum = 0;
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
	linenum = 0;
}

void Dialog::Update(float dTime, float pX, float pY)
{
	this->pX = pX;
	this->pY = pY;
	dT += dTime;
	if (iter->speaker == 0)
	{
		dialogbox->setPosition(pX - 128, pY - 98);
		portraits[0]->setPosition(pX - 122, pY - 92);

		top = false;
		pd = 0;
	}
	else
	{
		dialogbox->setPosition(pX - 128, pY + 58);
		switch (iter->speaker)
		{
		case -1: pd = 1; break;
		case -2: pd = 2; break;
		case -3: pd = 3; break;
		case 10: pd = 18; break;
		case 11: pd = 17; break;
		case 100: pd = 15; break;
		case 1: pd = 10; break;
		case 2: pd = 11; break;
		case 3: pd = 12; break;
		case 4: pd = 13; break;
		case 5: pd = 14; break;
		case 6: pd = 19; break;
		}
		portraits[pd]->setPosition(pX - 122, pY + 64);

		top = true;
	}

	numChars = dT / 50;
	if (linenum < (signed)iter->text.size() && numChars >= (signed)iter->text[linenum].size())
	{
		linenum++;
		dT = 0;
		numChars = 0;
	}
	else if (linenum == iter->text.size())
	{
		waiting = false;
	}
}

void Dialog::_DrawText()
{
	for (int i = 0; i < linenum; i++)
	{
		top ? tY = pY + 92 - 8 * i : tY = pY - 64 - 8 * i;
		drawText(iter->text[i], pX - 78, tY, iter->text[i].size());
	}
	top ? tY = pY + 92 - 8 * linenum : tY = pY - 64 - 8 * linenum;
	if (linenum < (signed)iter->text.size())
		drawText(iter->text[linenum], pX - 78, tY, numChars);
}

void Dialog::_DrawBox()
{
	dialogbox->draw(0.25);
	portraits[pd]->draw(1);
}

