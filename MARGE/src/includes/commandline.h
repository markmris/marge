#pragma once

#include <string_view>
#include "camera.h"

enum struct args 
{
	marge,
	pixelsamples,
	raydepth,
	focusdistance,
	defocusangle
};

constexpr std::string_view enumToString(args arg);

args enumFromString(auto str);

void initializeEngine(int argc, char* argv[], camera camera);
void setValue(int* var, const char* i);
void setValue(double* var, const char* i);