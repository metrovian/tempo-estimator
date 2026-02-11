#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;
	uint32_t data_size;
	int16_t *data;
} wav_pcm16_t;
#pragma pack(pop)

extern int wav_read(wav_pcm16_t *wav, const char *path);
extern void wav_free(wav_pcm16_t *wav);