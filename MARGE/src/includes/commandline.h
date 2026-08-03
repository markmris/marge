#pragma once

#include <string_view>

enum struct args 
{
	marge,
	pixelsamples,
	raydepth,
	focusdistance,
	defocusangle
};

constexpr std::string_view enumToString(args arg);

void initializeEngine(int argc, char* argv[]);