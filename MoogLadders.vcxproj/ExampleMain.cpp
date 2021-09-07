#if defined(_MSC_VER)
    #pragma comment(lib, "dsound.lib")
#endif
#include "AudioDevice.h"
#include "NoiseGenerator.h"
#include <iostream>
#include <sndfile.h>
#include "sndfile.hh"
#include "StilsonModel.h"
#include "OberheimVariationModel.h"
#include "SimplifiedModel.h"
#include "ImprovedModel.h"
#include "HuovilainenModel.h"
#include "KrajeskiModel.h"
#include "RKSimulationModel.h"
#include "MicrotrackerModel.h"
#include "MusicDSPModel.h"
#include "RKSimulationModel.h"


#include <thread>
#include <chrono>
#include <vector>

int main()
{
	AudioDevice::ListAudioDevices();
	
	//int desiredSampleRate = 44100;


	#define NUM_CHANNELS 2
	#define SAMPLE_RATE 26040
	
	std::string infile_name = "C:/Users/mwcm/Documents/GitHub/pitcher/warning6ud1.wav";

	// Open input file.
	SndfileHandle infile_handle(infile_name);

	if (!infile_handle || infile_handle.error() != 0)
	{
		return 1;
	}

	// Show file stats
	int64_t in_frames = infile_handle.frames();
	int in_channels = infile_handle.channels();
	int in_samplerate = infile_handle.samplerate();

	// Read audio data as float
	std::vector<float> in_data(in_frames * in_channels);
	infile_handle.read(in_data.data(), in_data.size());


	AudioDevice device(2, SAMPLE_RATE);
	device.Open(device.info.id);

	ImprovedMoog improvedModel(SAMPLE_RATE);
	improvedModel.Process(in_data.data(), in_data.size());

	StilsonMoog stilsonModel(SAMPLE_RATE);
	//stilsonModel.Process(noiseSamples.data(), noiseSamples.size());
	
	SimplifiedMoog simplifiedModel(SAMPLE_RATE);
	//simplifiedModel.Process(noiseSamples.data(), noiseSamples.size());
	
	HuovilainenMoog huovilainenModel(SAMPLE_RATE);
	//huovilainenModel.Process(noiseSamples.data(), noiseSamples.size());

	MicrotrackerMoog microtrackerModel(SAMPLE_RATE);
	//microtrackerModel.Process(noiseSamples.data(), noiseSamples.size());

	MusicDSPMoog musicdspModel(SAMPLE_RATE);
	//musicdspModel.Process(noiseSamples.data(), noiseSamples.size());
	
    KrajeskiMoog aaronModel(SAMPLE_RATE);
	//aaronModel.Process(noiseSamples.data(), noiseSamples.size());

	RKSimulationMoog rkModel(SAMPLE_RATE);
	//rkModel.Process(noiseSamples.data(), noiseSamples.size());
	
	OberheimVariationMoog oberheimModel(SAMPLE_RATE);
	//oberheimModel.Process(noiseSamples.data(), noiseSamples.size());
	
	const int len = infile_handle.frames() / SAMPLE_RATE;

	SF_INFO sfinfo;

	sfinfo.channels = 1;
	sfinfo.samplerate = 44100;
	sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	

	const char* filename = "C:/Users/mwcm/Documents/GitHub/pitcher/warning6ud1_FILTERED.wav";

	SNDFILE* outfile = sf_open(filename, SFM_WRITE, &sfinfo);

	sf_count_t count = sf_writef_float(outfile, in_data.data(), in_data.size());

	const char* error = sf_strerror(outfile);
	std::cout << error << "\n";
	sf_close(outfile);
	// file = SndfileHandle("C:/Users/mwcm/Documents/GitHub/pitcher/warning6ud1_FILTERED.wav", SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, 2, SAMPLE_RATE);
	
	// device.Play(in_data);
	
	return 0;
}
