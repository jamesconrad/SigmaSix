

#include "Sprite.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
//#include "drawPrimitives.h"
#include <string>
#include <vector>
#include <fstream>

#ifndef ENTTYPE_S
#define ENTTYPE_S
enum entitytype {
	PLAYER = 0,
	ENEMY = 10,
	ELITE = 11,
	NEUTRAL = -1,
	BOSS = 100,
	MINIBOSS1 = 1,
	MINIBOSS2 = 2,
	MINIBOSS3 = 3,
	MINIBOSS4 = 4,
	MINIBOSS5 = 5,
	MINIBOSS6 = 6
};
#endif

struct speech
{
	std::vector<std::string> text;
	speech* next;
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
	bool Speaking();
	void Next();

private:
	Dialog();

	speech* head;
	speech* iter;
	Sprite* dialogbox;
	std::vector<Sprite*> portraits;
};