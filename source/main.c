#include "wav.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "./tempo-estimator music.wav\n");
		return -1;
	}

	wav_pcm16_t wav = {0};
	if (wav_read(&wav, (const char *)argv[1]) == 0) {
		fprintf(stderr, "audio_format: %u\n", (unsigned)wav.audio_format);
		fprintf(stderr, "num_channels: %u\n", (unsigned)wav.num_channels);
		fprintf(stderr, "sample_rate: %u\n", wav.sample_rate);
		fprintf(stderr, "byte_rate: %u\n", wav.byte_rate);
		fprintf(stderr, "block_align: %u\n", (unsigned)wav.block_align);
		fprintf(stderr, "bits_per_sample: %u\n", (unsigned)wav.bits_per_sample);
		fprintf(stderr, "data_size: %u\n", wav.data_size);
		wav_free(&wav);
	}

	return 0;
}