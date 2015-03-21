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
	void KeyPress(unsigned char key, bool press);
	void ChangeImage(int newImage);
	bool StartGame() { return startGame; }

private:
	std::vector<Sprite*> effects;
	Sprite* background;
	int selection;
	bool startGame;
	bool keys[256];

};



#endif MENU