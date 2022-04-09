#include "SampleDataManager.h"

std::vector<unsigned short> SampleDataManager::UnpackAll(const std::vector<char>& bytes)
{
	const static int bytesPerSample = 2;
	auto numSamples = bytes.size() / bytesPerSample;

	auto result = new std::vector<unsigned short>(numSamples);

	for (int i = 0; i < bytes.size() - 1; i += bytesPerSample)
	{
		unsigned short sample = (bytes[i] & 0xff) | bytes[i + 1] << 8;

		result->push_back(sample);
	}

	return *result;
}

std::vector<char> SampleDataManager::PackAll(const std::vector<unsigned short>& samples)
{
	const static int bytesPerSample = 2;

	auto result = new std::vector<char>(samples.size() * bytesPerSample);

	for (int i = 0; i < samples.size(); i++)
	{
		char byte1 = (samples[i] >> 0) & 0xFF;
		char byte2 = (samples[i] >> 8) & 0xFF;

		result->push_back(byte1);
		result->push_back(byte2);
	}

	return *result;
}
