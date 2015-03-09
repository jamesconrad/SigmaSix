#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>

class Script
{
public:
	Script(char* path);
	void Update(float dTime);
private:
	std::vector<std::string> cmd;
};

#endif SCRIPT_H