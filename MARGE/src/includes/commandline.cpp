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

args enumFromString(auto str)
{
	if (str == "marge") return args::marge;
	else if (str == "--pixelsamples") return args::pixelsamples;
	else if (str == "--raydepth") return args::raydepth;
	else if (str == "--focusdistance") return args::focusdistance;
	else if (str == "--defocusangle") return args::defocusangle;
}

void initializeEngine(int argc, char* argv[], camera camera)
{
	for (int i = 0; i < argc; i++)
	{
		switch (enumFromString(std::string(argv[i])))
		{
		case args::marge:
			if (argc == 1)
				return;
			else
				continue;

		case args::pixelsamples:
			
		}
	}
}