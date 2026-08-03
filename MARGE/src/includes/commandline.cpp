#include "commandline.h"
#include <iostream>
#include <format>

constexpr std::string_view enumToString(args arg)
{
	switch (arg)
	{
	case args::marge: return "marge";
	case args::pixelsamples: return "--pixelsamples";
	case args::raydepth: return "--raydepth";
	case args::focusdistance: return "--focusdistance";
	case args::defocusangle: return "--defocusangle";
	}
}

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