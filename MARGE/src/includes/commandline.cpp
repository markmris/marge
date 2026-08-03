#include "commandline.h"
#include <iostream>
#include <format>

void initializeEngine(int argc, char* argv[])
{
	if (argc == 1 && (argv[0]) == "marge")
		return;
	else
		throw std::invalid_argument(std::format("Invalid argument: Unknown keyword '{}'", argv[0]));

	for (int i = 1; i <= argc; i++)
	{

	}
}