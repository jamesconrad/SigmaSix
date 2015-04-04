#ifndef DIALOG_H
#define DIALOG_H

#include "drawPrimitives.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <fstream>

#ifndef ENTTYPE_S
#define ENTTYPE_S
enum entitytype {
	PLAYER = 0,
	ENEMY = 10,
	ELITE = 11,
	NEUTRAL1 = -1,
	NEUTRAL2 = -2,
	NEUTRAL3 = -3,
	BOSS = 100,
	MINIBOSS1 = 1,
	MINIBOSS2 = 2,
	MINIBOSS3 = 3,
	MINIBOSS4 = 4,
	MINIBOSS5 = 5,
	MINIBOSS6 = 6,
	F1 = -101,
	F2 = -102,
	F3 = -103,
	F4 = -104,
	F5 = -105,
	F6 = -106,
};
#endif

struct speech
{
	std::vector<std::string> text;
	speech* next;
	int speaker;
};

class Dialog
{
public:
	static Dialog* instance()
	{
		static Dialog* instance = new Dialog();
		return instance;
	}

	void Say(entitytype, int diaNum);
	void _DrawText();
	void _DrawBox();
	void Update(float dTime, float pX, float pY);
	bool MoreText() { return moreText; }
	bool Waiting() { return waiting; }
	void Next();
	void Skip();

private:
	Dialog();
	std::string ReturnFP(int num);
	std::string ReturnSearch(int num);
	void ResetSay();

	float dT;
	bool moreText;
	bool waiting;
	bool top;
	int linenum;
	int pd;
	float pX, pY, tY;
	int numChars;
	speech* head;
	speech* iter;
	Sprite* dialogbox;
	std::vector<Sprite*> portraits;
};

#endif