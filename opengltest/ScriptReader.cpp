#include "ScriptReader.h"

/*
SYNTAX:
command arg1 arg2 arg3...

COMMANDS:

Attach [tarType] [target]
Move [tarX] [tarY]
Freeze
*/


Script::Script(char* filepath)
{
	step = 0;
	nextArg = true;
	std::string line;
	file.open(filepath, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			cmd.push_back(line);
			cmd.at(cmd.size()).append("\n");
		}
		file.close();
	}
	else
		printf("ERROR: Could not open script at: %s\n", filepath);
}

void Script::Update(float dTime)
{
	if (cmd.size() < 1)
		return;

	if (nextArg)
	{
		int space = cmd.at(step).find(' ');
		int eol = cmd.at(step).find('\n');
		curArg = cmd.at(step).substr(0, space - 1);
		
		std::stringstream stream(cmd.at(step).substr(space + 1, eol));
		int n;
		while (stream >> n)
			args.push_back(n);
	}

	if (curArg.compare("Attach"))
	{
		switch (args[0])
		{
		case 1: tarType = ENTITY; break;
		case 2: tarType = PROJ; break;
		}
		target = args[1];
	}
	else if (curArg.compare("Move"))
	{
		switch (tarType)
		{
		case 1:
			if (args[0] > EntityManager::instance()->getXofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(EntityManager::instance()->SpeedOfID(target).x * dTime ,0));
		}
	}
}