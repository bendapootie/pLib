#pragma once

#include "Types\Types.h"

//--------------------------------------------------------------------------------------
// Simple psudo-random number generator
//--------------------------------------------------------------------------------------

class Random
{
public:
	static constexpr int32 kMaxValue = 0x7fffffff;

public:
	Random() {}
	Random(uint64 seed) : seed_(seed) {}

	int32 Next()
	{
		// Take the seed and return a value between 0 and 32767
		Step();
		return (seed_ >> 32) & 0x7fffffff;
	}

	int32 Next(const int max_value)
	{
		// TODO: See if there's a better way to return a more even distribution
		return Next() % max_value;
	}

	int32 Next(const int min_value, const int max_value)
	{
		return min_value + Next(max_value - min_value);
	}

	float NextF()
	{
		return static_cast<float>(Next()) / static_cast<float>(kMaxValue);
	}

	float NextF(const float max_value)
	{
		return max_value * NextF();
	}

	float NextF(const float min_value, const float max_value)
	{
		return min_value + NextF(max_value - min_value);
	}

private:
	// Simple linear congruential generator
	inline void Step() { seed_ = 6364136223846793005 * seed_ + 1442695040888963407; }

private:
	// Starting seed is 5323
	uint64 seed_ = 5323;
};
