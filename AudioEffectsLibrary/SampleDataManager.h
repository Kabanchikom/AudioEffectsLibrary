#pragma once
#include <vector>

class SampleDataManager
{
public:
	/// <summary>
	/// Unpack array of bytes into array of samples.
	/// </summary>
	std::vector<float> UnpackAll(const std::vector<char>& bytes);

	/// <summary>
	/// Pack array of asmples into array of bytes.
	/// </summary>
	std::vector<char> PackAll(const std::vector<float>& samples);

	double FullScale(int bitsPerSample);

	long ExtendSign(long temp, int bitsPerSample);
};