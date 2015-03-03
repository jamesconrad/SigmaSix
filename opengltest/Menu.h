#ifndef MENU
#define MENU

#include "Sprite.h"
#include <vector>

class MenuClass
{
public:
	MenuClass();
	void Draw();
	void Update(float dTime);


private:
	std::vector<Sprite*> effects;
	Sprite* background;


};



#endif MENU