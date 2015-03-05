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
	//button == GLUT_ABCD_BUTTON
	//state == GLUT_DOWN || GLUT_UP
	void MouseClick(int button, int state, int x, int y);


private:
	std::vector<Sprite*> effects;
	Sprite* background;


};



#endif MENU