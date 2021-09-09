#if defined(_MSC_VER)
    #pragma comment(lib, "dsound.lib")
#endif

#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "ImprovedModel.h"


int main() {
	return 0;
}

std::vector<float> filter(
	std::vector<float> in_data,
	int cutoff = 1500,
	int resonance = 0.1f,
	int sample_rate = 26040,
	int num_channels = 2
)
{

	ImprovedMoog improvedModel(sample_rate);
	improvedModel.SetCutoff(cutoff);
	improvedModel.SetResonance(resonance);
	improvedModel.Process(in_data.data(), in_data.size());

	return in_data;
}

// this isn't going to work
// vector is incompatible with C

// might be quicker to just rewrite the base model and improved model in python

extern "C" {
	std::vector<float> moog_filter(std::vector<float> a)
	{
		return filter(a);
	}
}