#if defined(_MSC_VER)
    #pragma comment(lib, "dsound.lib")
#endif

#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <sndfile.h>
#include "sndfile.hh"
#include "ImprovedModel.h"


int main(int cutoff = 1500, int resonance = 0.1f, int sample_rate = 26040, int num_channels = 2)
{	
	std::string infile_name = "C:/Users/mwcm/Documents/GitHub/pitcher/808.wav";

	// Open input file.
	SndfileHandle infile_handle(infile_name);

	if (!infile_handle || infile_handle.error() != 0)
	{
		return 1;
	}

	// file stats
	int64_t in_frames = infile_handle.frames();
	int in_channels = infile_handle.channels();
	int in_samplerate = infile_handle.samplerate();

	// Read audio data as float
	std::vector<float> in_data(in_frames * in_channels);
	infile_handle.read(in_data.data(), in_data.size());

	ImprovedMoog improvedModel(sample_rate);
	improvedModel.SetCutoff(cutoff);
	improvedModel.SetResonance(resonance);
	improvedModel.Process(in_data.data(), in_data.size());

	const int len = infile_handle.frames() / sample_rate;

	SF_INFO sfinfo;

	std::ostringstream oss;
	oss << "C:/Users/mwcm/Documents/GitHub/pitcher/808_cutoff_" << cutoff << "_resonance_" << resonance << ".WAV";
	std::string aeiou = oss.str();
	const char* filename = aeiou.c_str();

	sfinfo.channels = 1;
	sfinfo.samplerate = 44100;
	sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

	SNDFILE* outfile = sf_open(filename, SFM_WRITE, &sfinfo);

	sf_count_t count = sf_writef_float(outfile, in_data.data(), in_data.size());

	const char* error = sf_strerror(outfile);
	std::cout << error << "\n";
	sf_close(outfile);
	
	return 0;
}
