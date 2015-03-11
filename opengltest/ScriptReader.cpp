#include "ScriptReader.h"

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

	}
}