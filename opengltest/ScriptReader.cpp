#include "ScriptReader.h"
#include "Dialog.h"
#include "TileManager.h"
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
	complete = false;
	std::string line;
	file.open(filepath, std::ios::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			cmd.push_back(line);
			cmd.at(cmd.size() - 1).append("\n");
		}
		file.close();
	}
	else
	{
		printf("ERROR: Could not open script at: %s\n", filepath);
		complete = true;
	}
}

void Script::Update(float dTime)
{
	if (step >= (signed)cmd.size())
	{
		complete = true;
		return;
	}
	EntityManager::instance()->Update(dTime);

	if (Dialog::instance()->MoreText())
		return;

	if (nextArg)
	{
		args.clear();
		int space = cmd.at(step).find(' ');
		int eol = cmd.at(step).find('\n');
		curArg = cmd.at(step).substr(0, space);
		
		std::stringstream stream(cmd.at(step).substr(space + 1, cmd.at(step).size()));
		int n;
		for (int i = 0, s = stream.end; i < s; i++)
		{
			stream >> n;
			args.push_back(n);
		}
		//while (stream >> n && stream.end)
		//	args.push_back(n);
		nextArg = false;
		step++;
	}

	if (curArg.compare("Attach") == 0)
	{
		switch (args[0])
		{
		case 1: tarType = ENTITY; break;
		case 2: tarType = PROJ; break;
		}
		target = args[1];
		nextArg = true;
	}
	else if (curArg.compare("Move") == 0)
	{
		switch (tarType)
		{
		case 1:
			//X
			//incase they are very close
			if (args[0] - EntityManager::instance()->getXofID(target) < 1 && args[0] - EntityManager::instance()->getXofID(target) > -1)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(args[0] - EntityManager::instance()->getXofID(target), 0));
			}
			//incase they are far
			else if (args[0] > EntityManager::instance()->getXofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(EntityManager::instance()->SpeedOfID(target) * dTime ,0));
			else if (args[0] < EntityManager::instance()->getXofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(EntityManager::instance()->SpeedOfID(target) * dTime * -1.0, 0));
			//Y
			//incase they are very close
			if (args[1] - EntityManager::instance()->getYofID(target) < 1 && args[1] - EntityManager::instance()->getYofID(target) > -1)
			{
				EntityManager::instance()->ModPosOfID(target, vec2(0, args[1] - EntityManager::instance()->getYofID(target)));
			}
			//incase they are far
			else if (args[1] > EntityManager::instance()->getYofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(0, EntityManager::instance()->SpeedOfID(target) * dTime));
			else if (args[1] < EntityManager::instance()->getYofID(target))
				EntityManager::instance()->ModPosOfID(target, vec2(0, EntityManager::instance()->SpeedOfID(target) * dTime * -1.0));
			//check if there
			if (args[0] - EntityManager::instance()->getXofID(target) < 1 && args[0] - EntityManager::instance()->getXofID(target) > -1 && args[1] - EntityManager::instance()->getYofID(target) < 1 && args[1] - EntityManager::instance()->getYofID(target) > -1)
				nextArg = true;
		}
	}
	else if (curArg.compare("Freeze") == 0)
	{
		if (args[0] != 0)
			EntityManager::instance()->FreezeID(target, true);
		else
			EntityManager::instance()->FreezeID(target, false);
		nextArg = true;
	}
	else if (curArg.compare("Kill") == 0)
	{
		EntityManager::instance()->DeleteEntity(args[0]);
		nextArg = true;
	}
	else if (curArg.compare("Say") == 0)
	{
		Dialog::instance()->Say(EntityManager::instance()->GetType(target), args[0]);
		nextArg = true;
	}
	else if (curArg.compare("Breakout\n") == 0)
	{
		TileManager::instance()->ReplaceTile(112, 128, STATIC, 112, 128, 16, 16, 305, 170, false);
		TileManager::instance()->ReplaceTile(112, 112, STATIC, 112, 112, 16, 16, 220, 136, false);
		
		ColisionManager::instance()->RebuildColisionMap();

		nextArg = true;
	}
}