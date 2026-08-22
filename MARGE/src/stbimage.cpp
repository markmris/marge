#ifdef _MSC_VER
	#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb/stb_image.h"

#include <cstdlib>
#include <iostream>
#include <filesystem>

const std::filesystem::path textureDir = "textures/";

struct image
{
	const int bytesPerPixel = 3;
	int bytesPerScanline = 0;
	float* fdata = nullptr;
	unsigned char* bdata = nullptr;
	int imageWidth = 0;
	int imageHeight = 0;

	image() {}
	image(const std::string& imageFileName)
	{
		// Find image
		std::filesystem::path imageDir = textureDir / imageFileName;

		if (!std::filesystem::exists(imageDir))
		{
			std::cerr << "ERROR: Image not found with name: " << imageFileName;

			return;
		}

		// Load image
		int n = bytesPerPixel;
		fdata = stbi_loadf(imageDir.string().c_str(), &imageWidth, &imageHeight, &n, bytesPerPixel);

		if (fdata == nullptr)
		{
			std::cerr << "Could not load image at filepath " << imageDir.string();
			return;
		}

		bytesPerScanline = imageWidth * bytesPerPixel;
	}

	~image()
	{
		delete[] bdata;
		STBI_FREE(fdata);
	}

	const unsigned char* pixelData(int x, int y) const
	{
		static unsigned char magenta[] = { 255, 0, 255 };
		if (bdata == nullptr) return magenta;

		x = std::clamp(x, 0, imageWidth);
		y = std::clamp(y, 0, imageHeight);

		return bdata + y * bytesPerScanline + x * bytesPerScanline;
	}

	static unsigned char floatToByte(float value)
	{
		return static_cast<unsigned char>(
			std::clamp(value, 0.0f, 255.0f / 256.0f) * (256.0f)
		);
	}

	void convertToBytes()
	{
		int totalBytes = imageWidth * imageHeight * bytesPerPixel;
		bdata = new unsigned char[totalBytes];

		auto *bPtr = bdata;
		auto *fPtr = fdata;

		for (int i = 0; i < totalBytes; i++, bPtr++, fPtr++)
		{
			*bPtr = floatToByte(*fPtr);
		}
	}
};

#ifdef _MSVC_VER
	#pragma warning (pop)
#endif