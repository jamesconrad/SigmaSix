#ifndef MENU
#define MENU

#include "Sprite.h"
#include <vector>

class MenuClass
{
public:
	MenuClass(int num);
	void Draw();
	void Update(float dTime);
	//button == GLUT_ABCD_BUTTON
	//state == GLUT_DOWN || GLUT_UP
	void MouseClick(int button, int state, int x, int y);
	void ChangeImage(int newImage);

private:
	std::vector<Sprite*> effects;
	Sprite* background;
	int selection;

};



#endif MENU