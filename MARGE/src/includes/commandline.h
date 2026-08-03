#pragma once

enum struct args 
{
	marge,
	pixelsamples,
	raydepth,
	focusdistance,
	defocusangle
};

void initializeEngine(int argc, char* argv[]);