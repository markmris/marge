#include "commandline.h"
#include <iostream>
#include <format>
#include <string>

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
				break;

		case args::pixelsamples:
			if (argv[i + 1] != nullptr)
				setValue(&camera.maxPixelSamples, argv[i + 1]);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::raydepth:
			if (argv[i + 1] != nullptr)
				setValue(&camera.maxDepth, argv[i + 1]);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::focusdistance:
			if (argv[i + 1] != nullptr)
				setValue(&camera.focusDistance, argv[i + 1]);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::defocusangle:
			if (argv[i + 1] != nullptr)
				setValue(&camera.defocusAngle, argv[i + 1]);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		default:
			break;
		}
	}
}

void setValue(int* var, const char* i)
{
	try
	{
		*var = std::stoi(i);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(std::format("Invalid argument '{}', must be an integer!", i));
	}
}

void setValue(double* var, const char* i)
{
	try
	{
		*var = std::stod(i);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(std::format("Invalid argument '{}', must be a number!", i));
	}
}