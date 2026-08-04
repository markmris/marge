#include "commandline.h"
#include <iostream>
#include <format>
#include <string>
#include <typeindex>

args enumFromString(auto str)
{
	if (str == "--help") return args::help;
	else if (str == "--pixelsamples") return args::pixelsamples;
	else if (str == "--raydepth") return args::raydepth;
	else if (str == "--focusdistance") return args::focusdistance;
	else if (str == "--defocusangle") return args::defocusangle;
	else if (str == "--fov") return args::fov;
	else if (str == "--pitch") return args::pitch;
	else if (str == "--yaw") return args::yaw;
	else if (str == "--objectcount") return args::objectcount;

	else
	{
		try
		{
			str = std::stod(str);
			return args::value;
		}
		catch (const std::exception& e)
		{
			throw std::invalid_argument(std::format("Invalid argument '{}'", str));
		}
	}
}

bool initializeEngine(int argc, char* argv[], camera& camera, int& globalObjectCount)
{
	for (int i = 1; i < argc; i++)
	{
		switch (enumFromString(std::string(argv[i])))
		{
		case args::help:
			if (argv[i + 1] == nullptr)
			{
				return true;
			}
			else
			{
				throw std::invalid_argument("Error: --help must be used by itself with no additional arguments.");
			}
				
			break;

		case args::pixelsamples:
			if (argv[i + 1] != nullptr)
				setValue(&camera.maxPixelSamples, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::raydepth:
			if (argv[i + 1] != nullptr)
				setValue(&camera.maxDepth, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::focusdistance:
			if (argv[i + 1] != nullptr)
				setValue(&camera.focusDistance, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::defocusangle:
			if (argv[i + 1] != nullptr)
				setValue(&camera.defocusAngle, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::fov:
			if (argv[i + 1] != nullptr)
				setValue(&camera.fov, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::pitch:
			if (argv[i + 1] != nullptr)
				setValue(&camera.pitch, argv[i + 1], true);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::yaw:
			if (argv[i + 1] != nullptr)
				setValue(&camera.yaw, argv[i + 1], true);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::objectcount:
			if (argv[i + 1] != nullptr)
				setValue(&globalObjectCount, argv[i + 1], false);
			else
				throw std::invalid_argument(std::format("Error: Additional argument expected after '{}'", argv[i]));

			break;

		case args::value:
			break;
		}
	}

	return false;
}

void setValue(int* var, const char* i, bool signPresent)
{
	try
	{
		signPresent ? *var = std::stoi(i) : *var = std::abs(std::stoi(i));
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(std::format("Invalid argument '{}', must be an integer!", i));
	}
}

void setValue(double* var, const char* i, bool signPresent)
{
	try
	{
		signPresent ? *var = std::stod(i) : *var = std::fabs(std::stod(i));
		
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument(std::format("Invalid argument '{}', must be a number!", i));
	}
}