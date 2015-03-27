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
	
}

void deleteList(speech** head_ref)
{
	/* deref head_ref to get the real head */
	speech* current = *head_ref;
	speech* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	/* deref head_ref to affect the real head back
	in the caller. */
	*head_ref = NULL;
}

void Dialog::ResetSay()
{
	deleteList(&head);
	head = new speech;
	head->next = NULL;
	iter = head;
}

void Dialog::Draw(float dTime)
{

}
