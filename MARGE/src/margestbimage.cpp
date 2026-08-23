#ifdef _MSC_VER
	#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include "margestbimage.h"

const std::filesystem::path textureDir = "textures/";

constexpr int image::bytesPerPixel = 3;

image::image() {}
image::image(const std::string& imageFileName)
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

image::~image()
{
	delete[] bdata;
	STBI_FREE(fdata);
}

const unsigned char* image::pixelData(int x, int y) const
{
	static unsigned char magenta[] = { 255, 0, 255 };
	if (bdata == nullptr) return magenta;

	x = std::clamp(x, 0, imageWidth - 1);
	y = std::clamp(y, 0, imageHeight - 1);

	const size_t offset = static_cast<size_t>(y) * bytesPerScanline + static_cast<size_t>(x) * bytesPerPixel;

	return &bdata[offset];
}

unsigned char image::floatToByte(float value)
{
	return static_cast<unsigned char>(
		std::clamp(value, 0.0f, 255.0f / 256.0f) * (256.0f)
	);
}

void image::convertToBytes()
{
	int totalBytes = imageWidth * imageHeight * bytesPerPixel;
	bdata = new unsigned char[totalBytes];

	auto* bPtr = bdata;
	auto* fPtr = fdata;

	for (int i = 0; i < totalBytes; i++, bPtr++, fPtr++)
	{
		*bPtr = floatToByte(*fPtr);
	}
}

#ifdef _MSC_VER
	#pragma warning (pop)
#endif