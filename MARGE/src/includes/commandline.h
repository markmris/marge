#pragma once

#include "camera.h"

enum struct args 
{
	help,
	pixelsamples,
	raydepth,
	focusdistance,
	defocusangle,
	fov,
	yaw,
	pitch,

	value // For handling numbers in enumFromString
};

args enumFromString(auto str);

void initializeEngine(int argc, char* argv[], camera& camera);
void setValue(int* var, const char* i);
void setValue(double* var, const char* i);