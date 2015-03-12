#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "EntityManager.h"
#include "ProjectileManager.h"

enum targetType
{
	NONE = 0,
	ENTITY = 1,
	PROJ = 2
};

class Script
{
public:
	Script(char* path);
	void Update(float dTime);
private:
	std::vector<std::string> cmd;
	int step;
	std::string curArg;
	std::vector<int> args;
	std::ifstream file;
	bool nextArg;
	int target;
	targetType tarType;
};

#endif SCRIPT_H