#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <Windows.h>
#include <Xinput.h>

class Controller
{
private:
	int cId;
	XINPUT_STATE state;

	float deadzoneX;
	float deadzoneY;

public:
	static Controller* instance()
	{
		static Controller* instance = new Controller();
		return instance;
	}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

	int  GetPort();
	XINPUT_GAMEPAD *GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);

private:
	Controller() : deadzoneX(0.05f), deadzoneY(0.02f) {}
	Controller(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}
};

#endif