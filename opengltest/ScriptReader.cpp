#include "ScriptReader.h"

/*
SYNTAX:
command arg1 arg2 arg3...

COMMANDS:

Attach [tarType] [target]
Move [tarX] [tarY]
Freeze [true(1),false(0)]
Kill [target]
Say [linenumber]
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
		nextArg = false;
	}

	if (curArg.compare("Attach"))
	{
		switch (args[0])
		{
		case 1: tarType = ENTITY; break;
		case 2: tarType = PROJ; break;
		}
		target = args[1];
		nextArg = true;
	}
	else if (curArg.compare("Move"))
	{
		switch (tarType)
		{
		case 1:
			//X
			//incase they are very close
			if (args[0] - EntityManager::instance()->getXofID(target) < 1 && args[0] - EntityManager::instance()->getXofID(target) > 0)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(args[0] - EntityManager::instance()->getXofID(target), 0));
				nextArg = true;
			}
			else if (args[0] - EntityManager::instance()->getXofID(target) > -1 && args[0] - EntityManager::instance()->getXofID(target) < 0)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(args[0] - EntityManager::instance()->getXofID(target), 0));
				nextArg = true;
			}
			//incase they are far
			else if (args[0] > EntityManager::instance()->getXofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(EntityManager::instance()->SpeedOfID(target) * dTime ,0));
			else if (args[0] < EntityManager::instance()->getXofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(EntityManager::instance()->SpeedOfID(target) * dTime * -1.0, 0));
			//Y
			//incase they are very close
			if (args[1] - EntityManager::instance()->getYofID(target) < 1 && args[1] - EntityManager::instance()->getYofID(target) > 0)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(0, args[1] - EntityManager::instance()->getYofID(target)));
				nextArg = true;
			}
			else if (args[1] - EntityManager::instance()->getYofID(target) > -1 && args[1] - EntityManager::instance()->getYofID(target) < 0)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(0, args[1] - EntityManager::instance()->getYofID(target)));
				nextArg = true;
			}
			else if (args[1] > EntityManager::instance()->getYofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(0, EntityManager::instance()->SpeedOfID(target) * dTime));
			else if (args[1] < EntityManager::instance()->getYofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(0, EntityManager::instance()->SpeedOfID(target) * dTime * -1.0));
		}
	}
	else if (curArg.compare("Freeze"))
	{
		if (args[0] != 0)
			EntityManager::instance()->FreezeID(target, true);
		else
			EntityManager::instance()->FreezeID(target, false);
	}
	else if (curArg.compare("Kill"))
	{
		EntityManager::instance()->DeleteEntity(args[0]);
	}
	else if (curArg.compare("Say"))
	{
		switch (args[1])
		{
		case 1: printf("Fuck you."); break;
		}
	}
}