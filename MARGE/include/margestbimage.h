#pragma once

#include "stb/stb_image.h"

#include <cstdlib>
#include <iostream>
#include <filesystem>

extern const std::filesystem::path textureDir;

struct image
{
	static const int bytesPerPixel;
	int bytesPerScanline = 0;
	float* fdata = nullptr;
	unsigned char* bdata = nullptr;
	int imageWidth = 0;
	int imageHeight = 0;

	image();
	image(const std::string& iamgeFileName);
	~image();

	const unsigned char* pixelData(int x, int y) const;
	static unsigned char floatToByte(float value);
	void convertToBytes();
};