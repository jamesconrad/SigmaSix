#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

enum targetType
{
	ENTITY = 0,
	PROJECTILE = 1
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