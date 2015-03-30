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
	bool StartGame() { return startGame; }
	void Pause() { startGame = false; }
	void setSelection(int num){ selection = num; ChangeImage(num); stopGame = false; }
	bool StopGame() { return stopGame; }

private:
	std::vector<Sprite*> effects;
	Sprite* background;
	int selection;
	bool startGame;
	bool keys[256];
	void ChangeImage(int newImage);
	bool stopGame = true;
};



#endif MENU