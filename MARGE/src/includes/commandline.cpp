#include "commandline.h"
#include <iostream>
#include <format>
#include <string>
#include <typeindex>

const std::string helpmessage = R"(
------------------- HELP MENU ---------------------------

How to use the MARGE command line:
The MARGE command line was designed for simplicity and ease of use. Each command must start with the executable's name which varies for each operating system.

EXAMPLE USAGE:
Windows - ./MARGE.exe --pixelsamples 20 --focusDistance 7.5
Linux - ./MARGE.exe --pixelsamples 20 --focusDistance 7.5
MacOS - NOT YET COMPATIBLE

You can modify any of the following interal variables:
(Note that variables are reset each time MARGE finishes rendering. If you want to reuse or modify a specific line, press the up arrow on your keyboard.)

--objectcount (integer) The amount of objects to be rendered in the scene. Has some performance impact the higher it is. Default set to 20
--pixelsamples (integer). The higher this number is, the better the image looks, but the longer it takes to render. Default set to 32. Anything around 50 looks pretty good, but takes a while.
--rayDepth (integer). The higher this is, the more realistic reflections will look. Default set to 13.
--focusDistance (decimal) The distance from the camera where objects are perfectly in focus. This is disabled when defocusAngle is set to 0. Default set to 8.0.
--defocusAngle (decimal). The higher this number is, the more blurred objects will look the further they are from the focus distance. Default set to 0.6.
--fov (decimal). The lower this number is, the more zoomed in the camera is. Default set to 90.

WARNING: MARGE is still in early development and is heavily unoptimized. Expect slow rendering, even on high-end computers.

WARNING: These variables are hard to control and are recommended to be left untouched.
--yaw (decimal). The left-right rotation of the camera. Set in degrees. Default set to 0.
--pitch (decimal) The up-down rotation of the camera. Set in degrees. Default set to -40.

--------------------------------------------------------- 
)";

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