#include "wav.h"

extern int wav_read(wav_pcm16_t *wav, const char *path) {
	if (wav == NULL) {
		return -1;
	} else if (path == NULL) {
		return -2;
	}

	FILE *fp = fopen(path, "rb");
	if (fp == NULL) {
		return -3;
	}

	char id[4] = {0};
	if (fread(id, 1, 4, fp) != 4) {
		fclose(fp);
		return -4;
	} else if (strncmp(id, "RIFF", 4) != 0) {
		fclose(fp);
		return -5;
	}

	uint32_t size = 0;
	fread(&size, 4, 1, fp);
	if (fread(id, 1, 4, fp) != 4) {
		fclose(fp);
		return -6;
	} else if (strncmp(id, "WAVE", 4) != 0) {
		fclose(fp);
		return -7;
	}

	int fmt_found = 0;
	int data_found = 0;
	while (data_found == 0) {
		if (fread(id, 1, 4, fp) != 4 ||
		    fread(&size, 4, 1, fp) != 1) {
			break;
		} else if (strncmp(id, "fmt ", 4) == 0) {
			fmt_found = 1;
			if (fread(&wav->audio_format, 2, 1, fp) != 1 ||
			    fread(&wav->num_channels, 2, 1, fp) != 1 ||
			    fread(&wav->sample_rate, 4, 1, fp) != 1 ||
			    fread(&wav->byte_rate, 4, 1, fp) != 1 ||
			    fread(&wav->block_align, 2, 1, fp) != 1 ||
			    fread(&wav->bits_per_sample, 2, 1, fp) != 1) {
				fclose(fp);
				return -8;
			} else if (size > 16) {
				fseek(fp, size - 16, SEEK_CUR);
			}
		} else if (strncmp(id, "data", 4) == 0) {
			data_found = 1;
			wav->data_size = size;
			wav->data = (int16_t *)malloc(size);
			if (wav->data == NULL) {
				fclose(fp);
				return -9;
			} else if (fread(wav->data, 1, size, fp) != size) {
				free(wav->data);
				fclose(fp);
				return -10;
			}
		} else {
			fseek(fp, size, SEEK_CUR);
		}
	}

	fclose(fp);
	if (fmt_found == 0 ||
	    data_found == 0) {
		return -11;
	} else if (
	    wav->audio_format != 1 ||
	    wav->bits_per_sample != 16) {
		return -12;
	}

	return 0;
}

extern void wav_free(wav_pcm16_t *pcm) {
	if (pcm != NULL) {
		if (pcm->data != NULL) {
			free(pcm->data);
			pcm->data = NULL;
		}
	}

	return;
}