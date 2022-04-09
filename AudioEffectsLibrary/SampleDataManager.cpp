#include "SampleDataManager.h"

std::vector<float> SampleDataManager::UnpackAll(const std::vector<char>& bytes)
{
	const static int bitsPerSample = 16;
	const static int bytesPerSample = bitsPerSample / 8;

	auto numSamples = bytes.size() / bytesPerSample;
	double fullScale = FullScale(bitsPerSample);

	auto result = new std::vector<float>(numSamples);

	for (int i = 0; i < bytes.size() - 1; i += bytesPerSample)
	{
		long temp = (bytes[i] & 0xffL) | bytes[i + 1] << 8L;
		float sample = 0L;

		// if encoding == pcm signed
		temp = ExtendSign(temp, bitsPerSample);
		sample = (float)(temp / fullScale);

		result->push_back(sample);
	}

	return *result;
}

std::vector<char> SampleDataManager::PackAll(const std::vector<float>& samples)
{
	const static int bitsPerSample = 16;
	const static int bytesPerSample = bitsPerSample / 8;

	double fullScale = FullScale(bitsPerSample);

	auto result = new std::vector<char>(samples.size() * bytesPerSample);

	for (int i = 0; i < samples.size(); i++)
	{
		float sample = samples[i];
		long temp = 0L;

		// if encoding == pcm signed
		temp = (long)(sample * fullScale);

		char byte1 = (temp >> 0) & 0xffL;
		char byte2 = (temp >> 8L) & 0xffL;

		result->push_back(byte1);
		result->push_back(byte2);
	}

	return *result;
}

// Computes the largest magnitude representable by the audio format,
// with pow(2.0, bitsPerSample - 1).
// 
// This is used for scaling the float array to the -1.0f to 1.0f range
double SampleDataManager::FullScale(int bitsPerSample)
{
	return pow(2.0, bitsPerSample - 1);
}

long SampleDataManager::ExtendSign(long temp, int bitsPerSample) 
{
	int extensionBits = 64 - bitsPerSample;
	return (temp << extensionBits) >> extensionBits;
}